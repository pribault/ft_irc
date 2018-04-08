/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rfc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 10:39:27 by pribault          #+#    #+#             */
/*   Updated: 2018/04/08 22:17:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RFC_H
# define RFC_H

/*
***************
**	defines  **
***************
*/

/*
**	register protocol:
**		PASS
**		NICK
**		USER
**
**	PASS is optionnal
*/

# define PASS		"PASS"
# define NICK		"NICK"
# define USER		"USER"

/*
**	ping poooooong
*/

# define PING		"PING"
# define PONG		"PONG"

/*
**	messages
*/

# define NOTICE		"NOTICE"

/*
**	responses
*/

# define RPL_NONE	"RPL_NONE"

/*
**	message separator
*/

# define CRLF		"\r\n"
# define CRLF_SIZE	2

/*
**	parameter separator
*/

# define SPACE		" "

/*
**	paramters types
*/

# define PARAM_NUMBER	"0123456789"
# define PARAM_LETTERS	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define PARAM_SPECIAL	"-[]\\`^{}"
# define PARAM_WHITE	" \r\n"

/*
**	message formatage
*/

# define PREFIX_MAX		64
# define COMMAND_MAX	64

# define PARAMS_MAX		15
# define PARAMS_LEN		32

typedef struct		s_prefix
{
	char			name[PREFIX_MAX];
	char			user[PREFIX_MAX];
	char			host[PREFIX_MAX];
}					t_prefix;

typedef struct		s_message
{
	t_prefix		prefix;
	char			command[COMMAND_MAX];
	char			params[PARAMS_MAX][PARAMS_LEN];
	char			*end;
}					t_message;

# define PREFIX_DEFAULT	(t_prefix){{'\0'}, {'\0'}, {'\0'}}

#endif
