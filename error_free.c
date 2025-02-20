/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:01:11 by junjun            #+#    #+#             */
/*   Updated: 2025/02/20 01:06:32 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void error_exit(const char *msg)
{
	printf(RED"%s\n"DEFAULT, msg);
	exit(EXIT_FAILURE);
}