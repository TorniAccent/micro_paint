#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_shape
{
	char r;
	float x;
	float y;
	float w;
	float h;
	char c;
	struct s_shape *next;
} shape;
	

typedef struct s_frame
{
	int width;
	int height;
	char bc;
} frame;

int parser(FILE *file, frame *f, shape *s)
{
	int num, len = 0;

	if (fscanf(file, "%d %d %c\n", &f->width, &f->height, &f->bc) != 3)
		return (0);
	if (!(f->width > 0 && f->width <= 300 && f->height > 0 && f->height <= 300))
		return (0);
	s = (shape *)malloc(sizeof(shape));
	s->next = 0;
	while ((num = fscanf(file, "%c %f %f %f %f %c\n", &s->r, &s->x, &s->y, &s->w, &s->h, &s->c)) == 6)
	{
		len++;
		s->next = (shape *)malloc(sizeof(shape));
		s = s->next;
		s->next = 0;
	}
	if (num == 0)
		return (len);
	else
		return (0);
		
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(1, "Error: argument\n", 16);
        return (1);
    }

    FILE *file;
	if (!(file = fopen(av[1], "r")))
    {
        write(1, "Error: Operation file corrupted\n", 32);
		return (1);
    }

	frame *f;
	shape *s;
	if (!parser(file, f, s))
		return (1);
	for (; s->next; s = s->next)
	{
		for (int i = 0; i < f->height; i++)
		{
			for (int j = 0; j < f->width; j++)
			{
				if (s->r == 'r')
				{
					if ((s->x - 1 < j && j <= s->x || s->x + s->w - 1 < j && j <= s->x + s->w) &&
						(s->y - 1 < i && i <= s->y || s->y + s->h - 1 < i && i <= s->y + s->h) &&
						s->x - 1 < j && j <= s->x + s->w && s->y - 1 < i && i <= s->y + s->h)
						write(1, &s->c, 1);
					else write(1, &f->bc, 1);
				}
				else if (s->r == 'R')
				{
					if (s->x - 1 < j && j <= s->x + s->w &&
						s->y - 1 < i && i <= s->y + s->h)
						write(1, &s->c, 1);
					else write(1, &f->bc, 1);
				}
			}
			write(1, "\n", 1);
		}
	}
	return (0);
}