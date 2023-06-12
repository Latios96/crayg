#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_IDCONSTANTS_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_IDCONSTANTS_H_

#include <QString>

#define CRAYG_DEFINE_UI_ID(name) static const inline QString name = #name;

namespace crayg {

class IDs {
  public:
    CRAYG_DEFINE_UI_ID(statusProgressBar);
};

} // crayg

#endif // CRAYG_SRC_STANDALONEGUI_WIDGETS_IDCONSTANTS_H_
