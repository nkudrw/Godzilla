#ifndef GODTYPEDEF_H
#define GODTYPEDEF_H

#include <QObject>

//レンズ情報
//TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））→とりあえず全部double(植木)
typedef struct _LensInfo {
    Q_GADGET
    Q_PROPERTY(double pan MEMBER pan)
    Q_PROPERTY(double tilt MEMBER tilt)
    Q_PROPERTY(double zoom MEMBER zoom)
    Q_PROPERTY(double focus MEMBER focus)
    Q_PROPERTY(double iris MEMBER iris)
public:
    double pan;
    double tilt;
    double zoom;
    double focus;
    double iris;
}LensInfo;

Q_DECLARE_METATYPE(LensInfo)

//画角情報
//TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））→とりあえず全部double(植木)
typedef struct _AngleView {
    Q_GADGET
    Q_PROPERTY(double vertical MEMBER vertical)
    Q_PROPERTY(double horizontal MEMBER horizontal)
public:
    double vertical; //変数名適切??
    double horizontal; //変数名適切??
} AngleView;

Q_DECLARE_METATYPE(AngleView)

//位置情報
//TODO：型修正（適切な型が分からなかったのでとりあえず全部int（六車））→とりあえず全部double(植木)
typedef struct _Location {
    Q_GADGET
    Q_PROPERTY(double x MEMBER x)
    Q_PROPERTY(double y MEMBER y)
    Q_PROPERTY(double z MEMBER z)
    Q_PROPERTY(double angle MEMBER angle)
public:
    double x;
    double y;
    double z;
    double angle;
} Location;

Q_DECLARE_METATYPE(Location)

#endif // GODTYPEDEF_H
