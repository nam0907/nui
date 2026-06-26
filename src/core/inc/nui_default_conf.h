#ifndef __NUI_DEFAULT_CONF_H__
#define __NUI_DEFAULT_CONF_H__


#ifndef NUI_USE_FONT
	#define NUI_USE_FONT 										0
#endif                        					
																				
#ifndef NUI_USE_IMAGE         					
	#define NUI_USE_IMAGE 									0
#endif                        					
																				
#ifndef NUI_USE_GEOMETRY      					
	#define NUI_USE_GEOMETRY 								0
#endif                        					
																				
#ifndef NUI_USE_WIDGET        					
	#define NUI_USE_WIDGET 									0
#endif                        					
																				
#ifndef NUI_USE_MEMORY        					
	#define NUI_USE_MEMORY 									0
#endif 

#ifndef NUI_FONT_USE_SD	
	#if NUI_USE_FONT
		#define NUI_FONT_USE_SD 								NUI_USE_SD
	#endif
#endif 		
		
#ifndef NUI_IMAGE_USE_SD	
	#if NUI_USE_IMAGE
		#define NUI_IMAGE_USE_SD 								NUI_USE_SD
	#endif
#endif 

#ifndef NUI_FONT_USE_MEMORY
	#if NUI_USE_FONT
		#define NUI_FONT_USE_MEMORY 						NUI_USE_MEMORY
	#endif
#endif 

#ifndef NUI_IMAGE_USE_MEMORY	
	#if NUI_USE_IMAGE
		#define NUI_IMAGE_USE_MEMORY 						NUI_USE_MEMORY
	#endif
#endif 

#if NUI_FONT_USE_SD
	#ifndef NUI_FONT_USE_STREAM
		#define NUI_FONT_USE_STREAM 						1
	#endif
#endif

#if NUI_IMAGE_USE_SD
	#ifndef NUI_IMAGE_USE_STREAM
		#define NUI_IMAGE_USE_STREAM 						1
	#endif
#endif

#ifndef NUI_FONT_USE_STREAM
	#define NUI_FONT_USE_STREAM 							0
#endif

#ifndef NUI_IMAGE_USE_STREAM
	#define NUI_IMAGE_USE_STREAM 							0
#endif

#endif
