#include <functional>
#include <memory>

///// Tooling in order to store state
struct AnyState 
{
  virtual ~AnyState() = default;
};

template<class AnyFunctionStruct>
class StatefulFunctions
{
public:
  StatefulFunctions(std::unique_ptr<AnyState> && state) :
    state_(std::move(state)) {}

  AnyFunctionStruct * operator->() {
    return &functions_;
  }

  template<class State>
  State * state()
  {
    return dynamic_cast<State *> (state_.get());
  }

private:
  std::unique_ptr<AnyState> state_;
  AnyFunctionStruct functions_;
};
