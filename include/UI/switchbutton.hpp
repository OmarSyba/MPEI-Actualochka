#ifndef SWITCHBUTTON_HPP
#define SWITCHBUTTON_HPP

#include <QAbstractButton>
#include <QtWidgets>

class SwitchButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
    SwitchButton(QWidget* parent = nullptr);
    SwitchButton(const QBrush& brush, QWidget* parent = nullptr);

    QSize sizeHint() const override;

    QBrush brush() const;
    void setBrush(const QBrush &brush);

    int offset() const;
    void setOffset(int o);

protected:
    void enterEvent(QEnterEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    bool _switch;
    qreal _opacity;
    int _x, _y, _height, _margin;
    QBrush _thumb, _track, _brush;
    QPropertyAnimation *_anim = nullptr;
};

#endif // SWITCHBUTTON_HPP
