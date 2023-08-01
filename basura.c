		if (j <= (int)ft_strlen(map[i + 1]) - 1)
		{
			if (map[i + 1][j] == ' ')
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (0);
			if (map[i][j] == ' ')
				if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
					return (0);
		}
		else
			if (map[i][j] != '1')
				return (0);

	if (i != 0)
		if (j > (int)ft_strlen(map[i - 1]) - 1 && map[i][j] != '1')
			return (0);