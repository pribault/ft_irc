/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rfc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 10:39:27 by pribault          #+#    #+#             */
/*   Updated: 2018/04/09 23:24:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RFC_H
# define RFC_H

/*
*************
**	links  **
*************
*/

/*
**	RFC 2812:
**
**		https://tools.ietf.org/html/rfc2812
*/

/*
**	RFC 2813:
**
**		https://tools.ietf.org/html/rfc2813
*/

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

# define ADMIN		"ADMIN"
# define AWAY		"AWAY"

# define CONNECT	"CONNECT"

# define DIE		"DIE"

# define ERROR		"ERROR"

# define INFO		"INFO"
# define INVITE		"INVITE"
# define ISON		"ISON"

# define JOIN		"JOIN"

# define KICK		"KICK"
# define KILL		"KILL"

# define LINKS		"LINKS"
# define LIST		"LIST"
# define LUSERS		"LUSERS"

# define MODE		"MODE"
# define MOTD		"MOTD"

# define NAMES		"NAMES"
# define NICK		"NICK"
# define NOTICE		"NOTICE"

# define OPER		"OPER"

# define PART		"PART"
# define PASS		"PASS"
# define PING		"PING"
# define PONG		"PONG"
# define PRIVMSG	"PRIVMSG"

# define QUIT		"QUIT"

# define REHASH		"REHASH"
# define RESTART	"RESTART"

# define SERVICE	"SERVICE"
# define SERVLIST	"SERVLIST"
# define SQUERY		"SQUERY"
# define SQUIT		"SQUIT"
# define STATS		"STATS"
# define SUMMON		"SUMMON"

# define TIME		"TIME"
# define TOPIC		"TOPIC"
# define TRACE		"TRACE"

# define USER		"USER"
# define USERHOST	"USERHOST"
# define USERS		"USERS"

# define VERSION	"VERSION"

# define WALLOPS	"WALLOPS"
# define WHO		"WHO"
# define WHOIS		"WHOIS"
# define WHOWAS		"WHOWAS"

/*
**	responses
*/

# define RPL_WELCOME			"001"
# define RPL_YOURHOST			"002"
# define RPL_CREATED			"003"
# define RPL_MYINFO				"004"
# define RPL_BOUNCE				"005"

# define RPL_TRACELINK			"200"
# define RPL_TRACECONNECTING	"201"
# define RPL_TRACEHANDSHAKE		"202"
# define RPL_TRACEUNKNOWN		"203"
# define RPL_TRACEOPERATOR		"204"
# define RPL_TRACEUSER			"205"
# define RPL_TRACESERVER		"206"
# define RPL_TRACESERVICE		"207"
# define RPL_TRACENEWTYPE		"208"
# define RPL_TRACECLASS			"209"
# define RPL_TRACERECONNECT		"210"
# define RPL_STATSLINKINFO		"211"
# define RPL_STATSCOMMANDS		"212"

# define RPL_ENDOFSTATS			"219"

# define RPL_UMODEIS			"221"

# define RPL_SERVLIST			"234"
# define RPL_SERVLISTEND		"235"

# define RPL_STATSUPTIME		"242"
# define RPL_STATSOLINE			"243"

# define RPL_LUSERCLIENT		"251"
# define RPL_LUSEROP			"252"
# define RPL_LUSERUNKNOWN		"253"
# define RPL_LUSERCHANNELS		"254"
# define RPL_LUSERME			"255"
# define RPL_ADMINME			"256"
# define RPL_ADMINLOC1			"257"
# define RPL_ADMINLOC2			"258"
# define RPL_ADMINEMAIL			"259"

# define RPL_TRACELOG			"261"
# define RPL_TRACEEND			"262"
# define RPL_TRYAGAIN			"263"

# define RPL_AWAY				"301"
# define RPL_USERHOST			"302"
# define RPL_ISON				"303"

# define RPL_UNAWAY				"305"
# define RPL_NOWAWAY			"306"

# define RPL_WHOISUSER			"311"
# define RPL_WHOISSERVER		"312"
# define RPL_WHOISOPERATOR		"313"
# define RPL_WHOWASUSER			"314"
# define RPL_ENDOFWHO			"315"

# define RPL_WHOISIDLE			"317"
# define RPL_ENDOFWHOIS			"318"
# define RPL_WHOISCHANNELS		"319"

# define RPL_LISTSTART			"321"
# define RPL_LIST				"322"
# define RPL_LISTEND			"323"
# define RPL_CHANNELMODEIS		"324"
# define RPL_UNIQOPIS			"325"

# define RPL_NOTOPIC			"331"
# define RPL_TOPIC				"332"

# define RPL_INVITING			"341"
# define RPL_SUMMONING			"342"

# define RPL_INVITELIST			"346"
# define RPL_ENDOFINVITELIST	"347"
# define RPL_EXCEPTLIST			"348"
# define RPL_ENDOFEXCEPTLIST	"349"

# define RPL_VERSION			"351"
# define RPL_WHOREPLY			"352"
# define RPL_NAMREPLY			"353"

# define RPL_LINKS				"364"
# define RPL_ENDOFLINKS			"365"
# define RPL_ENDOFNAMES			"366"
# define RPL_BANLIST			"367"
# define RPL_ENDOFBANLIST		"368"
# define RPL_ENDOFWHOWAS		"369"

# define RPL_INFO				"371"
# define RPL_MOTD				"372"

# define RPL_ENDOFINFO			"374"
# define RPL_MOTDSTART			"375"
# define RPL_ENDOFMOTD			"376"

# define RPL_YOUREOPER			"381"
# define RPL_REHASHING			"382"
# define RPL_YOURESERVICE		"383"

# define RPL_TIME				"391"
# define RPL_USERSSTART			"392"
# define RPL_USERS				"393"
# define RPL_ENDOFUSERS			"394"
# define RPL_NOUSERS			"395"

/*
**	error responses
*/

# define ERR_NOSUCHNICK			"401"
# define ERR_NOSUCHSERVER		"402"
# define ERR_NOSUCHCHANNEL		"403"
# define ERR_CANNOTSENDTOCHAN	"404"
# define ERR_TOOMANYCHANNELS	"405"
# define ERR_WASNOSUCHNICK		"406"
# define ERR_TOOMANYTARGETS		"407"
# define ERR_NOSUCHSERVICE		"408"
# define ERR_NOORIGIN			"409"

# define ERR_NORECIPIENT		"411"
# define ERR_NOTEXTTOSEND		"412"
# define ERR_NOTOPLEVEL			"413"
# define ERR_WILDTOPLEVEL		"414"
# define ERR_BADMASK			"415"

# define ERR_UNKNOWNCOMMAND		"421"
# define ERR_NOMOTD				"422"
# define ERR_NOADMININFO		"423"
# define ERR_FILEERROR			"424"

# define ERR_NONICKNAMEGIVEN	"431"
# define ERR_ERRONEUSNICKNAME	"432"
# define ERR_NICKNAMEINUSE		"433"

# define ERR_NICKCOLLISION		"436"
# define ERR_UNAVAILRESOURCE	"437"

# define ERR_USERNOTINCHANNEL	"441"
# define ERR_NOTONCHANNEL		"442"
# define ERR_USERONCHANNEL		"443"
# define ERR_NOLOGIN			"444"
# define ERR_SUMMONDISABLED		"445"
# define ERR_USERSDISABLED		"446"

# define ERR_NOTREGISTERED		"451"

# define ERR_NEEDMOREPARAMS		"461"
# define ERR_ALREADYREGISTRED	"462"
# define ERR_NOPERMFORHOST		"463"
# define ERR_PASSWDMISMATCH		"464"
# define ERR_YOUREBANNEDCREEP	"465"
# define ERR_YOUWILLBEBANNED	"466"
# define ERR_KEYSET				"467"

# define ERR_CHANNELISFULL		"471"
# define ERR_UNKNOWNMODE		"472"
# define ERR_INVITEONLYCHAN		"473"
# define ERR_BANNEDFROMCHAN		"474"
# define ERR_BADCHANNELKEY		"475"
# define ERR_BADCHANMASK		"476"
# define ERR_NOCHANMODES		"477"
# define ERR_BANLISTFULL		"478"

# define ERR_NOPRIVILEGES		"481"
# define ERR_CHANOPRIVSNEEDED	"482"
# define ERR_CANTKILLSERVER		"483"
# define ERR_RESTRICTED			"484"
# define ERR_UNIQOPPRIVSNEEDED	"485"

# define ERR_NOOPERHOST			"491"

# define ERR_UMODEUNKNOWNFLAG	"501"
# define ERR_USERSDONTMATCH		"502"

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
# define PARAMS_LEN		128

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
	uint8_t			n_params;
}					t_message;

# define PREFIX_DEFAULT	(t_prefix){{'\0'}, {'\0'}, {'\0'}}

#endif
