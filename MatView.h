#ifndef _MAT_VIEW_H_
#define _MAT_VIEW_H_

#include<QOpenGLWidget>

class MatView :public QOpenGLWidget
{
    Q_OBJECT

public:
    MatView(QWidget *p);
    ~MatView();
    void paintEvent(QPaintEvent *e);
};

#endif
