#ifndef C_COMPILER_INSTRUCTION_HPP
#define C_COMPILER_INSTRUCTION_HPP

#include <memory>
#include <vector>

namespace x86
{
  class instruction {
   public:
    template <typename T>
      requires(!std::derived_from<std::decay_t<T>, instruction>)
    instruction(T&& i) : self(std::make_unique<Model<std::decay_t<T>>>(std::forward<T>(i))) {}

    instruction(const instruction& other) : self(other.self->clone_()) {}
    instruction& operator=(const instruction& other) {
      if (this != &other) self = other.self->clone_();
      return *this;
    }

    instruction(instruction&& other) noexcept = default;
    instruction& operator=(instruction&& other) noexcept = default;

    [[nodiscard]] std::string emit() const { return self->emit_(); }
    [[nodiscard]] bool is_legal() const { return self->is_legal_(); }
    [[nodiscard]] std::vector<instruction> legalize() { return self->legalize_(); }

   private:
    struct Concept
    {
      virtual ~Concept() = default;
      [[nodiscard]] virtual std::unique_ptr<Concept> clone_() const = 0;
      [[nodiscard]] virtual std::string emit_() const = 0;
      [[nodiscard]] virtual bool is_legal_() const = 0;
      [[nodiscard]] virtual std::vector<instruction> legalize_() = 0;
    };

    template <typename T>
    struct Model final : Concept
    {
      explicit Model(T t) : data(std::move(t)) {}
      [[nodiscard]] std::unique_ptr<Concept> clone_() const override {
        return std::make_unique<Model>(std::move(data));
      }
      [[nodiscard]] std::string emit_() const override { return data.emit(); }
      [[nodiscard]] bool is_legal_() const override {
        if constexpr (requires(T t) {
                        { t.is_legal() } -> std::convertible_to<bool>;
                      }) {
          return data.is_legal();
        }
        else {
          return true;
        }
      }

      [[nodiscard]] std::vector<instruction> legalize_() override {
        if constexpr (requires(T t) { t.legalize(); }) {
          return data.legalize();
        }
        else {
          return {instruction(data)};
        }
      }

      T data;
    };

    std::unique_ptr<Concept> self;
  };

  // using instruction_t = std::variant<start_function, mov, ret, unary, binary, pop, cdq, jmp, cmp, set, label>;
  //
  // // mov
  // std::vector<instruction_t> legalize(const mov& m);
  // // cmp
  // std::vector<instruction_t> legalize(const cmp& c);
  // // binary
  // std::vector<instruction_t> legalize(const binary& c);
}  // namespace x86
#endif
