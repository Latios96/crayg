
#ifndef CRAYG_SRC_STANDALONEGUI_STYLESHEET_H_
#define CRAYG_SRC_STANDALONEGUI_STYLESHEET_H_

const char *STYLESHEET = R"(
QWidget {
  font: 10pt Arial;
  color: #e3e3e3;
  background: #383838;
  selection-background-color: #bd9b54; }

  QWidget:disabled {
    color: #7a7a7a; }

    QScrollBar:horizontal, QScrollBar:vertical {
      background: #2a2a2a;
      border: 1px solid #2a2a2a; }

      QScrollBar:horizontal {
        border-bottom-right-radius: 4px;
        border-bottom-left-radius: 4px;
        border-top-left-radius: 4px;
        border-top-right-radius: 4px; }

        QScrollBar:vertical {
          border-bottom-right-radius: 4px;
          border-bottom-left-radius: 4px;
          border-top-left-radius: 4px;
          border-top-right-radius: 4px; }

          QScrollBar::handle:horizontal, QScrollBar::handle:vertical {
            background: #5a5a5a;
            border: 1px solid #5a5a5a;
            border-bottom-right-radius: 4px;
            border-bottom-left-radius: 4px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px; }

            QScrollBar::handle:horizontal {
              border-top-color: #7e7e7e;
              min-width: 45px; }

              QScrollBar::handle:vertical {
                border-left-color: #7e7e7e;
                min-height: 45px; }

                QScrollBar:left-arrow:horizontal, QScrollBar::right-arrow:horizontal,
                QScrollBar:left-arrow:vertical, QScrollBar::right-arrow:vertical {
                  background: transparent; }

                  QScrollBar::add-line:horizontal, QScrollBar::add-line:vertical {
                    background: transparent; }

                    QScrollBar::sub-line:horizontal, QScrollBar::sub-line:vertical {
                      background: transparent; }

                      QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal,
                      QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
                        background: transparent; }

)";

#endif //CRAYG_SRC_STANDALONEGUI_STYLESHEET_H_
