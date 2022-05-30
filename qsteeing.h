#pragma once


#include <QProxyStyle>
#include <QStyleOptionTab>
#include "user.h"
class QSteeing : public QProxyStyle
{
    Q_OBJECT

public:
    QSteeing();
    ~QSteeing();

    //初始化
    void Init();

    /* sizeFromContents
    *  用于设置Tab标签大小
    * 1.获取原标签大小
    * 2.宽高切换
    * 3.强制宽高
    * 4.return
    * */
    QSize sizeFromContents(ContentsType type, const QStyleOption* option,
        const QSize& size, const QWidget* widget) const;

    /* drawControl
 *  画控件
 * 1.过滤CE_TabBarTabLabel
 * 2.选择状态下的背景绘制
 *      a.获取Rect
 *      b.保存旧的画笔
 *      c.设置新画笔
 *      d.画 Rect
 *      e.恢复旧的画笔
 * 3.设定Text对齐及选中/非选中状态下的Text颜色
 * 4.过滤CE_TabBarTab，对其进行绘制
 * */
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const;




};
