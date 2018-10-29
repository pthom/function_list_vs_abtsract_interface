#include <functional>
#include <memory>


// Any state shall be overrident by all the states
struct AnyState
{
  virtual ~AnyState() = default;
};


// StatefulFunctionList contains the function list (which is accessible by the operator ->)
// It will be stored in the application code as a kind of "pointer to the function list",
// i.e an "interface implementation".
//
// It also contains a hidden state, which can only be accessed at creation time
// (when filling the function list implementations)
template<class AnyConcreteFunctionList>
class StatefulFunctionList
{
public:
  virtual ~StatefulFunctionList() = default;

  StatefulFunctionList(std::shared_ptr<AnyState> && state) : state_(state) {}

  // operator-> : access to the inner function list from the application code
  AnyConcreteFunctionList * operator->() {
    return &functions_;
  }

private:
  // the state is totally hidden from the application code
  std::shared_ptr<AnyState> state_; 
  AnyConcreteFunctionList functions_;
};
