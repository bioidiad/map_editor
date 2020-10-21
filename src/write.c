#include "editor.h"


int write_map(char *name, t_all *all)
{
    t_xy *temp;
    t_sect *temp_sect;

    
    float x = 0, y = 0;
    int i, j;
    j = 0;
    int flag = 1;
    
    while(y <= all->mapsize.y)
    {
        flag = 1;
        j = 0;
        temp_sect = all->sectors;
        
        while(j < all->num_sectors)
        {
            i = 0;
            temp = temp_sect->vertex;
            while(i < temp_sect->npoints)
            {
                if(y == temp->y)
                {
                    if(flag)
                    {
                        printf("vertex  %d   ", (int)y);
                        flag = 0;
                    }
                    printf(" %d", (int)temp->x);
                }
                temp++;
                i++;
            }
            j++;
            temp_sect++;
        }
        y++;
        if(!flag)
        printf("\n");

    }
    return (0);
}