#include <vector>

#include "kb_actions.h"
#include "matrix/matrix.h"
#include "mocks/mock_keymap.h"

#define _____ KeyboardAction()
#define KA(...) KeyboardAction(__VA_ARGS__)
#define MD(CHR) KA(Modifier::CHR)
#define LS(NUM) KA(ActionType::LayerShift, NUM)
#define PS(NUM) KA(ActionType::LayerPush, NUM)
#define PO() KA(ActionType::LayerPop)
#define RO(...) KA({__VA_ARGS__})
// Tap vs. Hold
#define TH(CHR, ACTION) KA(CHR, &ACTION)

// TODO: Add testing for Rotate & Tap+hold
void MockKeymap::setup(Matrix*) {
  // Create my stupid little test keymap:
  std::array<KeyboardAction, 5> l1{KA(1), KA(2), MD(Shf), LS(1), PS(2)};
  std::array<KeyboardAction, 5> l2{KA(3), _____, PS(2), _____, KA(4)};
  std::array<KeyboardAction, 5> l3{KA(5), _____, _____, PO(), KA(6)};
  layers = std::array<std::array<KeyboardAction, 5>, 3>{l1, l2, l3};
}

std::vector<const KeyboardAction*> MockKeymap::mapToActions(Scanner*) {
  // TODO
}
