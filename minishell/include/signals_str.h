/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** All signal error messages
*/

/* File created the 19/03/2018 at 10:09:31 by julian.frabel@epitech.eu */

#ifndef __SIGNAL_STR_H_
	#define __SIGNAL_STR_H_

	#define ERROR_SIGNAL_MSG_SIGHUP "Hangup"
	#define	ERROR_SIGNAL_MSG_SIGINT ""
	#define ERROR_SIGNAL_MSG_SIGQUIT "Quit"
	#define ERROR_SIGNAL_MSG_SIGILL "Illegal instruction"
	#define ERROR_SIGNAL_MSG_SIGTRAP "Trace/BPT trap"
	#define ERROR_SIGNAL_MSG_SIGABRT "Abort"
	#define ERROR_SIGNAL_MSG_SIGBUS "Bus error"
	#define ERROR_SIGNAL_MSG_SIGFPE "Floating exception"
	#define ERROR_SIGNAL_MSG_SIGKILL "Killed"
	#define ERROR_SIGNAL_MSG_SIGUSR1 "User signal 1"
	#define ERROR_SIGNAL_MSG_SIGSEGV "Segmentation fault"
	#define ERROR_SIGNAL_MSG_SIGUSR2 "User signal 2"
	#define ERROR_SIGNAL_MSG_SIGPIPE ""
	#define ERROR_SIGNAL_MSG_SIGALRM "Alarm clock"
	#define ERROR_SIGNAL_MSG_SIGTERM "Terminated"
	#define ERROR_SIGNAL_MSG_SIGSTKFLT "Stack limit exceeded"
	#define ERROR_SIGNAL_MSG_SIGCHLD ""
	#define ERROR_SIGNAL_MSG_SIGCONT ""
	#define ERROR_SIGNAL_MSG_SIGSTOP ""
	#define ERROR_SIGNAL_MSG_SIGTSTP ""
	#define ERROR_SIGNAL_MSG_SIGTTIN ""
	#define ERROR_SIGNAL_MSG_SIGTTOU ""
	#define ERROR_SIGNAL_MSG_SIGURG ""
	#define ERROR_SIGNAL_MSG_SIGXCPU "Cputime limit exceeded"
	#define ERROR_SIGNAL_MSG_SIGXFSZ "Filesize limit exceeded"
	#define ERROR_SIGNAL_MSG_SIGVTALRM "Virtual time alarm"
	#define ERROR_SIGNAL_MSG_SIGPROF "Profiling time alarm"
	#define ERROR_SIGNAL_MSG_SIGWINCH ""
	#define ERROR_SIGNAL_MSG_SIGIO "Pollable event occured"
	#define ERROR_SIGNAL_MSG_SIGPWR "Power failure"
	#define ERROR_SIGNAL_MSG_SIGSYS "Bad system call"
	#define ERROR_SIGNAL_MSG_SIG32 ""
	#define ERROR_SIGNAL_MSG_SIG33 ""
	#define ERROR_SIGNAL_MSG_SIGRTMIN "First Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMIN1 "Second Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMIN2 "Third Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMIN3 "Fourth Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMIN4 "Signal 38"
	#define ERROR_SIGNAL_MSG_SIGRTMIN5 "Signal 39"
	#define ERROR_SIGNAL_MSG_SIGRTMIN6 "Signal 40"
	#define ERROR_SIGNAL_MSG_SIGRTMIN7 "Signal 41"
	#define ERROR_SIGNAL_MSG_SIGRTMIN8 "Signal 42"
	#define ERROR_SIGNAL_MSG_SIGRTMIN9 "Signal 43"
	#define ERROR_SIGNAL_MSG_SIGRTMIN10 "Signal 44"
	#define ERROR_SIGNAL_MSG_SIGRTMIN11 "Signal 45"
	#define ERROR_SIGNAL_MSG_SIGRTMIN12 "Signal 46"
	#define ERROR_SIGNAL_MSG_SIGRTMIN13 "Signal 47"
	#define ERROR_SIGNAL_MSG_SIGRTMIN14 "Signal 48"
	#define ERROR_SIGNAL_MSG_SIGRTMIN15 "Signal 49"
	#define ERROR_SIGNAL_MSG_SIGRTMAX14 "Signal 50"
	#define ERROR_SIGNAL_MSG_SIGRTMAX13 "Signal 51"
	#define ERROR_SIGNAL_MSG_SIGRTMAX12 "Signal 52"
	#define ERROR_SIGNAL_MSG_SIGRTMAX11 "Signal 53"
	#define ERROR_SIGNAL_MSG_SIGRTMAX10 "Signal 54"
	#define ERROR_SIGNAL_MSG_SIGRTMAX9 "Signal 55"
	#define ERROR_SIGNAL_MSG_SIGRTMAX8 "Signal 56"
	#define ERROR_SIGNAL_MSG_SIGRTMAX7 "Signal 57"
	#define ERROR_SIGNAL_MSG_SIGRTMAX6 "Signal 58"
	#define ERROR_SIGNAL_MSG_SIGRTMAX5 "Signal 59"
	#define ERROR_SIGNAL_MSG_SIGRTMAX4 "Signal 60"
	#define ERROR_SIGNAL_MSG_SIGRTMAX3 "Fourth Last Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMAX2 "Third Last Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMAX1 "Second Last Realtime Signal"
	#define ERROR_SIGNAL_MSG_SIGRTMAX "Last Realtime Signal"

	extern const char *signals_str[64];

#endif /* !__SIGNAL_STR_H_ */
