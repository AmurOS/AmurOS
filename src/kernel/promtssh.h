void __sh_error(const char *format, ...)
{
	__std__printc("[ERROR] ", RED);
	char **arg = (char **)&format;

	int c;
	char buf[32];

	arg++;

	__std__memset(buf, 0, sizeof(buf));
	while ((c = *format++) != 0)
	{
		if (c != '%')
			__std__putcc(c, RED);
		else
		{
			char *p, *p2;
			int pad0 = 0, pad = 0;

			c = *format++;
			if (c == '0')
			{
				pad0 = 1;
				c = *format++;
			}

			if (c >= '0' && c <= '9')
			{
				pad = c - '0';
				c = *format++;
			}

			switch (c)
			{
			case 'd':
			case 'u':
			case 'x':
				__std__itoan(buf, c, *((int *)arg++));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";

			string:
				for (p2 = p; *p2; p2++)
					;
				for (; p2 < p + pad; p2++)
					__std__putcc(pad0 ? '0' : ' ', RED);
				while (*p)
					__std__putcc(*p++, RED);
				break;

			default:
				__std__putcc(*((int *)arg++), RED);
				break;
			}
		}
	}
	__std__newline();
}

void __sh_warning(const char *format, ...)
{
	__std__printc("[WARNING] ", YELLOW);
	char **arg = (char **)&format;

	int c;
	char buf[32];

	arg++;

	__std__memset(buf, 0, sizeof(buf));
	while ((c = *format++) != 0)
	{
		if (c != '%')
			__std__putcc(c, YELLOW);
		else
		{
			char *p, *p2;
			int pad0 = 0, pad = 0;

			c = *format++;
			if (c == '0')
			{
				pad0 = 1;
				c = *format++;
			}

			if (c >= '0' && c <= '9')
			{
				pad = c - '0';
				c = *format++;
			}

			switch (c)
			{
			case 'd':
			case 'u':
			case 'x':
				__std__itoan(buf, c, *((int *)arg++));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";

			string:
				for (p2 = p; *p2; p2++)
					;
				for (; p2 < p + pad; p2++)
					__std__putcc(pad0 ? '0' : ' ', YELLOW);
				while (*p)
					__std__putcc(*p++, YELLOW);
				break;

			default:
				__std__putcc(*((int *)arg++), YELLOW);
				break;
			}
		}
	}
	__std__newline();
}

void __sh_message(const char *format, ...)
{
	__std__printc("[MESSAGE] ", GREEN);
	char **arg = (char **)&format;

	int c;
	char buf[32];

	arg++;

	__std__memset(buf, 0, sizeof(buf));
	while ((c = *format++) != 0)
	{
		if (c != '%')
			__std__putcc(c, GREEN);
		else
		{
			char *p, *p2;
			int pad0 = 0, pad = 0;

			c = *format++;
			if (c == '0')
			{
				pad0 = 1;
				c = *format++;
			}

			if (c >= '0' && c <= '9')
			{
				pad = c - '0';
				c = *format++;
			}

			switch (c)
			{
			case 'd':
			case 'u':
			case 'x':
				__std__itoan(buf, c, *((int *)arg++));
				p = buf;
				goto string;
				break;

			case 's':
				p = *arg++;
				if (!p)
					p = "(null)";

			string:
				for (p2 = p; *p2; p2++)
					;
				for (; p2 < p + pad; p2++)
					__std__putcc(pad0 ? '0' : ' ', GREEN);
				while (*p)
					__std__putcc(*p++, GREEN);
				break;

			default:
				__std__putcc(*((int *)arg++), GREEN);
				break;
			}
		}
	}
	__std__newline();
}
