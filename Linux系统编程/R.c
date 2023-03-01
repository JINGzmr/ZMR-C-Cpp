// //递归调用
// //ls -R
// void mydls_R(char path[])
// {
//   printf("%s:\n",path);
//   DIR* dir_ptr;
//   struct dirent* direntp;
//   if((dir_ptr=opendir(path)) != NULL)//打开目录
//   {
//     while((direntp=readdir(dir_ptr)) != NULL)//读取当前目录文件
//     {
//       restored_ls(direntp);
//     }
//        sort(filenames,0,file_cnt-1);
//     int j=0;
//     int i=0;
//     for(j=0;j<file_cnt;++j)
//     {
//       if(has_aRl==1||has_Rl==1)
//       {
//           char temp1[PATH_MAX];
//          sprintf(temp1,"%s/%s",path,filenames[j]);
//          dostat(temp1,filenames[j]);
//         continue;
//       }
//       if(filenames[j][0]=='.'&&(has_aR!=1&&has_aRl!=1))
//         continue;
//       struct stat info;
//       char temp1[PATH_MAX];
//       sprintf(temp1,"%s/%s",path,filenames[j]);
//       if(lstat(temp1,&info)==-1)
//         perror(temp1);
//       int color=get_color(info);
//          if(has_s==1)
//           {
//              long long size=info.st_size/1024;
//                if(size<=4)
//                   printf("4   ");
//                else
//                   printf("%-4lld",size);
//            }
//       printf_name2(filenames[j],color);
//     }
//   }
//   printf("\n");
//   printf("\n");
//   file_cnt=0;
//   closedir(dir_ptr);
//   if((dir_ptr=opendir(path))==NULL)//打开目录
//     fprintf(stderr,"lsl:cannot open %s\n",path);
//   else
//   {
//     while((direntp=readdir(dir_ptr))!=NULL)
//     {
//       if(strcmp(direntp->d_name,".")==0||strcmp(direntp->d_name,"..")==0)
//         continue;
//       if(has_R==1)
//       {
//         if(direntp->d_name[0]=='.')
//           continue;
//       }
//       struct stat info;
//       char temp[PATH_MAX];
//       sprintf(temp,"%s/%s",path,direntp->d_name);
//       if(lstat(temp,&info)==-1)
//         perror(temp);
//       if(S_ISDIR(info.st_mode))//判断是否为目录，如果是目录就进入递归
//       {
//         ls_R(temp);
//       }

//     }
//   }
// }

// void myls_R(char path[])
// {
//     DIR* root;
//     int ret,n,m;
//     char c;
//     struct dirent* dir;
//     struct stat info;
//     char dirList[100][256];
//     root = opendir(path);
//     if(root == NULL)
//     {
//         perror("opendir error");
//         exit(1);
//     }
//     //展示根目录
//     printf("%s:\n",path);
//     n = 0;
//     while( (dir=readdir(root))!=NULL )
//     {
//         if(dir->d_name[0]=='.')
//         {
//             continue;
//         }
//         char temp[256];
//         char last = path[strlen(*path)-1];
//         if(last == '/')
//         {
//             sprintf(temp,"%s%s",path,dir->d_name);
//         }
//         else
//         {
//             sprintf(temp,"%s/%s",path,dir->d_name);
//         }
//         //printf("%s\n",temp);
//         ret = lstat(temp,&info);
//         if(ret < 0)
//         {
//             perror("lstat error");
//             exit(0);
//         }
//         c = GetFileTypeCh(info.st_mode);
//         //printf("name:%20s,type:%c,size:%ld\n",dir->d_name,c,info.st_size) ;
//         printf("%s\t",dir->d_name) ;
//         //路径为 目录，进行递归遍历
//         if(c == 'd')
//         {
//             strcpy(dirList[n++],temp);
//             if( n > 100 )
//             {
//                 n--;
//                 break;
//             }
//         }
//     }
//     closedir(root);
//     printf("\n\n");
//     //递归展示目录下的目录项
//     for(m = 0; m < n; m++)
//     {
//         ListDir(dirList[m]);
//     }
//     return;
// }