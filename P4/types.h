#ifndef P4_TYPES_H
#define P4_TYPES_H

#define NAME_LENGTH_LIMIT 20


typedef char tNickname[NAME_LENGTH_LIMIT];
typedef enum {standard, premium} tUserCategory;
typedef int tPlayTime;

typedef char tTitleVideo[NAME_LENGTH_LIMIT];
typedef struct tVideo {
    tTitleVideo titleVideo;
    tPlayTime playTime;
} tVideoItem;

#endif //P4_TYPES_H
