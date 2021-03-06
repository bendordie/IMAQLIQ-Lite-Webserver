/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdHandler.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshells <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:44:21 by cshells           #+#    #+#             */
/*   Updated: 2022/02/01 18:44:30 by cshells          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __FDHANDLER_HPP__
#define __FDHANDLER_HPP__

#include <unistd.h>

class FdHandler {


public:

    FdHandler(int fd = -1, bool own = true);
    virtual ~FdHandler();

    virtual void    handle(bool read, bool write) = 0;
    const int&      getFd() const;
    virtual bool    wantBeRead() const;
    virtual bool    wantBeWritten() const;

private:

    int     _fd;
    bool    _own_fd;

};

#endif //__FDHANDLER_HPP__
