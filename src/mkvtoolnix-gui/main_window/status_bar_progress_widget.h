#pragma once

#include "common/common_pch.h"

#include <QWidget>

#include "common/qt.h"

class QMouseEvent;

namespace mtx::gui {

namespace Ui {
class StatusBarProgressWidget;
}

class StatusBarProgressWidgetPrivate;
class StatusBarProgressWidget : public QWidget {
  Q_OBJECT

protected:
  MTX_DECLARE_PRIVATE(StatusBarProgressWidgetPrivate)

  std::unique_ptr<StatusBarProgressWidgetPrivate> const p_ptr;

  explicit StatusBarProgressWidget(StatusBarProgressWidgetPrivate &p);

public:
  explicit StatusBarProgressWidget(QWidget *parent = nullptr);
  virtual ~StatusBarProgressWidget();

  void retranslateUi();

public slots:
  void setProgress(int progress, int totalProgress);
  void setJobStats(int numPendingAutomatic, int numPendingManual, int numRunning, int numOther);
  void setNumUnacknowledgedWarningsOrErrors(int numWarnings, int numErrors);
  void updateWarningsAndErrorsIcons();

  void reset();

protected:
  void setLabelTexts();

  virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

}
