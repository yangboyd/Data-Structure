 /* algo11-1.c 调用bo11-1.c的程序 */
#include "c10-1.h" /* 定义KeyType、RedType及SqList */

void print(RedType t)
{
  printf("(%d,%d)", t.key, t.otherinfo);
}

void main()
{
  RedType r;
  int i, j;
  char fname[k][4], fout[5] = "out", s[3];
  LoserTree ls;
  for (i = 0; i < k; i++)
  { /* 依次打开f0,f1,f2,…,k个文件 */
//    _itoa(i, s, 10); /* 生成k个文件名f0,f1,f2,… */
    snprintf(s, sizeof(s), "%d", i);
    strcpy(fname[i], "f");
    strcat(fname[i], s);
    fp[i] = fopen(fname[i], "rb"); /* 以读的方式打开文件f0,f1,… */
    printf("有序子文件f%d的记录为:\n", i);
    do
    {
      j = fread(&r, sizeof(RedType), 1, fp[i]); /* 依次将f0,f1,…的数据读入r */
      if (j == 1)
        print(r); /* 输出r的内容 */
    } while (j == 1);
    printf("\n");
    rewind(fp[i]); /* 使fp[i]的指针重新返回f0,f1,…的起始位置，以便重新读入内存 */
  }
  fp[k] = fopen(fout, "wb"); /* 以写的方式打开大文件fout */
  K_Merge(ls, b); /* 利用败者树ls将k个输入归并段中的记录归并到输出归并段，即大文件fout */
  for (i = 0; i <= k; i++)
    fclose(fp[i]); /* 关闭文件f0,f1,…和文件fout */
  fp[k] = fopen(fout, "rb"); /* 以读的方式重新打开大文件fout验证排序 */
  printf("排序后的大文件的记录为:\n");
  i = 1;
  do
  {
    j = fread(&r, sizeof(RedType), 1, fp[k]); /* 将fout的数据读入r */
    if (j == 1)
      print(r); /* 输出r的内容 */
    if (i++%M == 0)
      printf("\n"); /* 换行 */
  } while (j == 1);
  printf("\n");
  fclose(fp[k]); /* 关闭大文件fout */
}
