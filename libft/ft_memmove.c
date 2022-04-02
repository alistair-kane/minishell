/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:42:29 by alkane            #+#    #+#             */
/*   Updated: 2021/12/07 22:28:29 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*sp;
	unsigned char		*dp;

	if (!dest && !src)
		return (dest);
	sp = (unsigned char *)src;
	dp = (unsigned char *)dest;
	if ((sp < dp) && (dp < (sp + n)))
	{
		dp = dp + n;
		sp = sp + n;
		while (n-- > 0)
			*--dp = *--sp;
	}
	else
		while (n--)
			*dp++ = *sp++;
	return (dest);
}

// int main()
// {
//     char str[50] = "I am going from Delhi to Gorakhpur";
//     printf( "Function:\tft_memmove with overlap\n" );
//     printf( "Orignal :\t%s\n",str);
//     printf( "Source:\t\t%s\n", str + 5 );
//     printf( "Destination:\t%s\n\n", str + 11 );
//     ft_memmove( str + 11, str + 5, 29 );
//     printf( "Result:\t\t%s\n", str );
//     return 0;
// }