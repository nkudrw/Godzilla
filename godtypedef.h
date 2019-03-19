#ifndef GODTYPEDEF_H
#define GODTYPEDEF_H

//レンズ情報
//TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））
typedef struct _LensInfo {
    int pan;
    int tilt;
    int zoom;
    int focus;
    int iris;
} LensInfo;

//画角情報
//TODO:型修正（適切な型が分からなかったのでとりあえず全部int（六車））
typedef struct _AngleView {
    int vertical; //変数名適切??
    int horizontal; //変数名適切??
} AngleView;

//位置情報
//TODO：型修正（適切な型が分からなかったのでとりあえず全部int（六車））
typedef struct _Location {
    int x;
    int y;
    int z;
} Location;

#endif // GODTYPEDEF_H
