#include "../../includes/builtins.h"

static t_env_node	*find_prev_env(t_env_node *node, char *key)
{
	if (!node || !(node->next))
		return (NULL);
	while (ft_strcmp(node->next->key, key)) // 다음 노드의 키와 인자로 받은 key가 일치하기 직전까지 prev 돌리기
	{
		node = node->next;
		if (!node->next)
			return (NULL); // 해당 노드 내에 key가 존재하지 않을 경우
	}
	return (node);
}

static void	disconnect_node(t_env_node *prev, t_env_node *cur)
{
	prev->next = cur->next; // prev의 next를 cur의 next로 연결해 주기
	cur->next = NULL;
	free_env_node(cur);
}

static int	check_error(char *key)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (key[++i])
	{
		if (key[i] == '=') // key에 '='이 포함되어 있으면 에러 처리
		{
			flag = printf("unset: '%s': not a valid identifier\n", key);
			break;
		}
	}
	return (flag);
}

int	mini_unset(t_env *env, char **cmd)
{
	t_env_node	*prev;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	while (cmd[++i])
	{
		if (check_error(cmd[i]))
		{
			flag = 1;
			continue;
		}
		prev = find_prev_env(env->h_node.next, cmd[i]);
		if (!prev)
			continue;
		disconnect_node(prev, prev->next);
	}
	if (flag)
		return (FAIL);
	return (SUCCESS);
}
