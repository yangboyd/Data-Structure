#include <stdio.h>         // 提供system原型
#include "WordList.h"       //**▲04 串**//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    FILE* fp;
    char line[MaxLineLen];
    
    char* bookinfo = "TestData.txt";    // 书目文件名
    char* bookidx  = "BookIdx.txt";     // 关键词索引文件名
    
    // 创建索引表
    Main(bookinfo, bookidx);
    
    // 显示索引表到屏幕
    if((fp = fopen(bookidx, "r"))!=NULL) {
        printf("---------索引表生成功！---------\n\n");

        //On macOS, get file path
        char path[512];
        int fd = fileno(fp);
        int ret = fcntl(fd, F_GETPATH, path);
        if (ret == -1) {
            perror("fcntl");
        } else {
            printf("File path: %s\n", path);
        }


        while(feof(fp)==FALSE) {
            fgets(line, MaxLineLen, fp);
            printf("%s", line);
            line[0]=0;
        }
    } else {
        printf("---------未发现索引表！---------\n");
    }
    
    return 0;
}
