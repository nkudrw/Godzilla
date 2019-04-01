#ifndef GODTYPEDEF_H
#define GODTYPEDEF_H

//レンズ情報
//TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））→とりあえず全部double(植木)
typedef struct _LensInfo {
    double pan;
    double tilt;
    double zoom;
    double focus;
    double iris;
} LensInfo;

//画角情報
//TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））→とりあえず全部double(植木)
typedef struct _AngleView {
    double vertical; //変数名適切??
    double horizontal; //変数名適切??
} AngleView;

//位置情報
//TODO：型修正（適切な型が分からなかったのでとりあえず全部int（六車））→とりあえず全部double(植木)
typedef struct _Location {
    double x;
    double y;
    double z;
    double angle;
} Location;

#endif // GODTYPEDEF_H
