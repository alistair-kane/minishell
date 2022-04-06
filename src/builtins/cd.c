/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:22:37 by alkane            #+#    #+#             */
/*   Updated: 2022/04/06 14:29:33 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// should return int of "args consumed"

// cd for example consumes itself = return 1
// cd modifiers 'current directory' char* each time it modifies the current dir
// 		current directory var initialized as home directory (from path vector)

