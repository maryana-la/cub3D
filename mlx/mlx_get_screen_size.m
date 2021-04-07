#import <AppKit/NSScreen.h>
// #import <AppKit/NSOpenGLView.h>
// #import <Cocoa/Cocoa.h>
// #import <OpenGL/gl3.h>

// #include "mlx_int.h"
// #include "mlx_new_window.h"
// #include "mlx_new_window.h"

void	mlx_get_screen_size(int *width, int *height)
{
	NSRect disp = [[NSScreen mainScreen] frame];
	*height = (int)disp.size.height;
	*width = (int)disp.size.width;
}