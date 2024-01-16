/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:32:55 by del-ganb          #+#    #+#             */
/*   Updated: 2024/01/16 21:31:35 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *get_line(char *str)
{
    int i;

    i = 0;
    if(!*str)
        return (NULL);
    while(str[i] && str[i] != '\n')
        i++;
    return (ft_substr(str, 0, i + 1));    
}

static char *free_buffer(char *str)
{
    int i;
    char *res;
    
    i = 0;
    if(!*str)
    {
        free(str);
        return (NULL);
    }
    while(str[i] && str[i] != '\n')
        i++;
    if(str[i] == '\n')
        i++;
    res = ft_strdup(&str[i]);
    free(str);
    return (res);
}

char *get_next_line(int fd)
{
    static char *buffer[4000];
    char *stash;
    char *my_line;
    ssize_t end;
    
    end = 1;
    if(fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    stash = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
    if(!stash)
        return (NULL);
    stash[0] = 0;
    while(end > 0 && !ft_strchr(stash, '\n'))
    {
        end = read(fd, stash, BUFFER_SIZE);
        if(end < 0)
            return (free(stash), free(buffer[fd]), NULL);
        stash[end] = '\0';
        buffer[fd] = ft_strjoin(buffer[fd], stash);
    }
    my_line = get_line(buffer[fd]);
    buffer[fd] = free_buffer(buffer[fd]);
    free(stash);
    return (my_line);
}


