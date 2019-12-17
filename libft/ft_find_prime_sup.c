/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_prime_sup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 22:12:29 by niduches          #+#    #+#             */
/*   Updated: 2019/12/01 22:12:49 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_prime(int nb)
{
	int i;

	i = 2;
	if (nb < 2)
		return (0);
	while (i <= nb / i)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int			ft_find_prime_sup(int nb)
{
	int i;

	i = 0;
	while (ft_prime(nb + i) == 0)
		i++;
	return (nb + i);
}
