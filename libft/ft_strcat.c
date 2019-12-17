/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:59:29 by niduches          #+#    #+#             */
/*   Updated: 2019/12/01 22:13:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char const *src)
{
	int	len;
	int i;

	len = 0;
	while (dest[len])
		len++;
	i = 0;
	while (src[i] != '\0')
	{
		dest[len] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}
