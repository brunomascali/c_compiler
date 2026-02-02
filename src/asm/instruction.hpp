#ifndef C_COMPILER_INSTRUCTION_HPP
#define C_COMPILER_INSTRUCTION_HPP

#include <memory>

namespace x86
{
  class instruction {
   public:
    template <typename T>
    instruction(T&& i) : self(std::make_unique<Model<std::decay_t<T>>>(std::forward<T>(i))) {}

    instruction(const instruction& other) : self(other.self->clone()) {}
    instruction& operator=(const instruction& other) {
      if (this != &other) self = other.self->clone();
      return *this;
    }

    instruction(instruction&& other) noexcept = default;
    instruction& operator=(instruction&& other) noexcept = default;

    [[nodiscard]] std::string emit() const { return self->emit_(); }

   private:
    struct Concept
    {
      virtual ~Concept() = default;
      virtual std::unique_ptr<Concept> clone() const = 0;
      [[nodiscard]] virtual std::string emit_() const = 0;
    };

    template <typename T>
    struct Model final : Concept
    {
      explicit Model(T t) : data(std::move(t)) {}
      [[nodiscard]] std::string emit_() const override { return data.emit(); }
      std::unique_ptr<Concept> clone() const override { return std::make_unique<Model>(std::move(data)); };

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
