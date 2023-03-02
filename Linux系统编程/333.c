#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define a 1
#define l 2
#define s 3
#define r 4
#define t 5
#define i 6
#define R 7
struct file
{
  char filename[256];
  struct stat statres;
};

void a_printf(int mode[], int tmp1, struct file *buff, int count);
static struct file *sort(struct file **buff, int count);
static struct file *r_sort(struct file **buff, int count);

void guid(struct stat statres);
void ggid(struct stat statres);
void perm(struct stat statres);
void do_ls(int mode[], char *path);
void ls_l(struct file *buff);
void ls_R(struct file *buff, int count, int mode[], char *path);

int main(int argc, char **argv)
{
  int mode[7];
  char path[1024];
  int none[7] = {0};
  int c;

  getcwd(path, sizeof(path));
  if (argc < 2) // 无参数
  {
    strcpy(path, "./");
    path[2] = '\0';
    do_ls(none, path);
    return 0;
  }

  for (int n = 1; n < argc; n++)
  {
    if (argv[n][0] != '-')
    {
      strcpy(path, argv[n]);
    }
  }
  int sum = strlen(argv[1]);
  while (sum > 1)
  {
    c = getopt(argc, argv, "alrtRis");
    if (c < 0)
      break;
    switch (c)
    {
    case 'a':
      mode[a] = 1;
    case 'l':
      mode[l] = 1;
      break;
    case 's':
      mode[s] = 1;
      break;
    case 'R':
      mode[R] = 1;
      break;
    case 't':
      mode[t] = 1;
      break;
    case 'i':
      mode[i] = 1;
      break;
    case 'r':
      mode[r] = 1;
      break;
    default:
      break;
    }
    sum--;
  }

  do_ls(mode, path);
}
void do_ls(int mode[], char *path) // 绝对路径
{
  chdir(path);
  int count = 0, tmp1 = 0, allsize_a = 0, allsize = 0;
  DIR *dir = NULL;
  struct dirent *ptr = NULL;

  struct file *buff = malloc(sizeof(struct file) * 1024);
  memset(buff, 0, sizeof(struct file) * 1024);
  struct file *start = buff;

  dir = opendir(path);
  if (dir == NULL)
  {
    exit(1);
  }
  // 循环录入
  while ((ptr = readdir(dir)) != NULL)
  {
    strcpy(buff->filename, ptr->d_name);
    stat(ptr->d_name, &(buff->statres));

    allsize_a += (buff->statres.st_blocks) / 2;
    if (buff->filename[0] != '.')
    {
      allsize += (buff->statres.st_blocks) / 2;
    }

    buff++;
    count++;
  }
  buff = start;
  tmp1 = count;

  if (mode[R] != 1)
  {
    a_printf(mode, tmp1, buff, count);
  }
  if (mode[R] == 1)
  {
    printf("%s:\n", path);
    ls_R(buff, count, mode, path);
  }
  free(buff);
  closedir(dir);
}

void ls_R(struct file *buff, int count, int mode[], char *path)
{
  for (int m = 0; m < count; m++)
  {
    char *tmp = (buff + m)->filename;
    if (mode[a] != 1)
    {
      if (mode[i] == 1 && tmp[0] != '.')
        printf("%-10ld ", (buff + m)->statres.st_ino);
      if (mode[s] == 1 && tmp[0] != '.')
        printf("%-4ld ", (buff + m)->statres.st_blocks / 2);
      if (mode[l] == 1 && tmp[0] != '.')
        ls_l((buff + m));

      if (tmp[0] != '.')
        printf("%s ", (buff + m)->filename);
      if (mode[l] == 1 && tmp[0] != '.')
        printf("\n");
    }
    if (mode[a] == 1)
    {
      if (mode[i] == 1)
        printf("%-10ld ", (buff + m)->statres.st_ino);
      if (mode[s] == 1)
        printf("%-4ld ", (buff + m)->statres.st_blocks / 2);
      if (mode[l] == 1)
        ls_l((buff + m));
      printf("%s ", (buff + m)->filename);
      if (mode[l] == 1)
        printf("\n");
    }
  }
  printf("\n");
  for (int m = 0; m < count; m++)
  {
    char *tmp = (buff + m)->filename;
    if (S_ISDIR((buff + m)->statres.st_mode) && tmp[0] != '.')
    {
      char path1[1024];
      char path2[1024];

      strcpy(path1, path);

      strcpy(path2, path1);

      // printf("%s",path);
      strcat(path2, "/");
      strcat(path2, (buff + m)->filename);
      do_ls(mode, path2);
    }
  }
}
void ls_l(struct file *buff)
{
  perm(buff->statres);
  printf("%5ld", buff->statres.st_nlink);
  guid(buff->statres);
  ggid(buff->statres);
  printf("%7ld", buff->statres.st_size);
  char time[32];
  strcpy(time, ctime(&(buff->statres.st_mtime)));
  time[strlen(time) - 5] = '\0';
  printf("%8s", time);
}
void a_printf(int mode[], int tmp1, struct file *buff, int count)
{
  if (mode[t] == 1)
  {
    buff = sort(&buff, count);
  }
  if (mode[r] == 1)
  {
    buff = r_sort(&buff, count);
  }

  while (tmp1 > 0)
  {
    char *tmp = buff->filename;
    if (mode[a] != 1)
    {
      if (mode[i] == 1 && tmp[0] != '.')
        printf("%-10ld ", buff->statres.st_ino);
      if (mode[s] == 1 && tmp[0] != '.')
        printf("%-4ld ", buff->statres.st_blocks / 2);
      if (mode[l] == 1 && tmp[0] != '.')
        ls_l(buff);
      if (tmp[0] != '.')
        printf("%s ", buff->filename);
      if (mode[l] == 1 && tmp[0] != '.')
        printf("\n");
    }
    if (mode[a] == 1)
    {
      if (mode[i] == 1)
        printf("%-10ld ", buff->statres.st_ino);
      if (mode[s] == 1)
        printf("%-4ld ", buff->statres.st_blocks / 2);
      if (mode[l] == 1)
        ls_l(buff);
      printf("%s ", buff->filename);
      if (mode[l] == 1)
        printf("\n");
    }
    tmp1--;
    buff++;
  }
}
static struct file *r_sort(struct file **buff, int count)
{
  for (int m = 1; m <= count - 1; m++)
  {
    for (int k = 0; k < count - m; k++)
    {
      if ((*buff + k)->filename[0] < (*buff + k + 1)->filename[0])
      {
        struct file q = (*buff)[k + 1];
        (*buff)[k + 1] = (*buff)[k];
        (*buff)[k] = q;
      }
    }
  }
  return *buff;
}

static struct file *sort(struct file **buff, int count)
{
  for (int m = 1; m <= count - 1; m++)
  {
    for (int k = 0; k < count - m; k++)
    {
      if ((*buff + k)->statres.st_mtime < (*buff + k + 1)->statres.st_mtime)
      {
        struct file q = (*buff)[k + 1];
        (*buff)[k + 1] = (*buff)[k];
        (*buff)[k] = q;
      }
    }
  }
  return *buff;
}

void guid(struct stat statres)
{
  struct passwd *id;
  char *uname;

  id = getpwuid(statres.st_uid);
  uname = id->pw_name;

  printf("%7s", uname);
}

void ggid(struct stat statres)
{
  struct group *id;
  char *gname;

  id = getgrgid(statres.st_uid);
  gname = id->gr_name;

  printf("%7s", gname);
}

void perm(struct stat statres)
{
  char str[1024] = {0};
  strcpy(str, "----------");

  if (S_ISDIR(statres.st_mode)) // 是否为目录
  {
    str[0] = 'd';
  }

  if (S_ISCHR(statres.st_mode)) // 是否为字符设置
  {
    str[0] = 'c';
  }

  if (S_ISBLK(statres.st_mode)) // 是否为块设备
  {
    str[0] = 'b';
  }
  if ((statres.st_mode & S_IRUSR))
  {
    str[1] = 'r';
  }
  if ((statres.st_mode & S_IWUSR))
  {
    str[2] = 'w';
  }
  if ((statres.st_mode & S_IXUSR))
  {
    str[3] = 'x';
  }
  if ((statres.st_mode & S_IRGRP))
  {
    str[4] = 'r';
  }
  if ((statres.st_mode & S_IWGRP))
  {
    str[5] = 'w';
  }
  if ((statres.st_mode & S_IXGRP))
  {
    str[6] = 'x';
  }
  if ((statres.st_mode & S_IROTH))
  {
    str[7] = 'r';
  }
  if ((statres.st_mode & S_IWOTH))
  {
    str[8] = 'w';
  }
  if ((statres.st_mode & S_IXOTH))
  {
    str[9] = 'x';
  }
  printf("%s ", str);
}