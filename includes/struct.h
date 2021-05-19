
#ifndef STRUCT_H
# define STRUCT_H

typedef enum	e_status
{
	status_env,
	status_export,
	none
}				status;

typedef enum	e_error
{
	cmd_not_found
}				t_error;



typedef struct s_env
{
	char			*key;
	char			*content;
	status			status;
	struct s_env	*next;
}					t_env;

typedef	struct		s_btree
{	
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;


typedef struct		s_command
{
	char			*com;
	char			*arg;
}					t_command;

typedef struct s_all
{
	t_env	*env;
	t_list	*gc;
}				t_all;

#endif
