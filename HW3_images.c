#include "HW3_images.h"

// 
//  Image data for bullet
// 

const uint8_t bulletBitMap[] =
{
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, //       #                                      
	0x1E, 0x08, 0x14, 0xF4, 0x00, 0x00, //    ####     #      # #  #### #               
	0x74, 0x00, 0xAD, 0x40, 0x00, 0x00, // #### #          # # ## # #                   
	0x2A, 0x01, 0x35, 0x80, 0xB8, 0x00, //   # # #        #  ## # ##       # ###        
	0xDF, 0x84, 0xDE, 0xDC, 0x00, 0x08, // ## ######    #  ## #### ## ###              #
	0x1C, 0x5A, 0x60, 0x01, 0x80, 0x00, //    ###   # ## #  ##            ##            
	0x10, 0x05, 0x50, 0x03, 0x04, 0x00, //    #         # # # #          ##     #       
	0x08, 0x0C, 0x78, 0x00, 0x00, 0x00, //     #       ##   ####                        
	0x00, 0x03, 0xB5, 0x00, 0x00, 0x00, //               ### ## # #                     
};

// 
//  Image data for pacman
// 

const uint8_t pacmanBitMap[] =
{
	0x00, 0x00, 0x00, 0x00, //                      
	0x00, 0x0F, 0xE0, 0x00, //             #######         
	0x00, 0x7F, 0xFC, 0x00, //          #############      
	0x01, 0xFF, 0xFF, 0x00, //        #################    
	0x07, 0xFF, 0xFF, 0x80, //      ####################   
	0x0F, 0xFF, 0xFF, 0xC0, //     ######################  
	0x1F, 0xFF, 0xFF, 0xE0, //    ######################## 
	0x1F, 0xFF, 0xFF, 0xF0, //    #########################
	0x3F, 0xFB, 0xFF, 0xF0, //   ########### ##############
	0x7F, 0xFB, 0xFF, 0xC0, //  ############ ############  
	0x7F, 0xFF, 0xFF, 0x80, //  ########################   
	0x7F, 0xFF, 0xFF, 0x00, //  #######################    
	0xFF, 0xFF, 0xFC, 0x00, // ######################      
	0xFF, 0xFF, 0xF8, 0x00, // #####################       
	0xFF, 0xFF, 0xE0, 0x00, // ###################         
	0xFF, 0xFF, 0xC0, 0x00, // ##################          
	0xFF, 0xFF, 0xC0, 0x00, // ##################          
	0xFF, 0xFF, 0xF0, 0x00, // ####################        
	0xFF, 0xFF, 0xF8, 0x00, // #####################       
	0xFF, 0xFF, 0xFE, 0x00, // #######################     
	0x7F, 0xFF, 0xFF, 0x00, //  #######################    
	0x7F, 0xFF, 0xFF, 0xC0, //  #########################  
	0x7F, 0xFF, 0xFF, 0xE0, //  ########################## 
	0x3F, 0xFF, 0xFF, 0xF0, //   ##########################
	0x1F, 0xFF, 0xFF, 0xF0, //    #########################
	0x1F, 0xFF, 0xFF, 0xE0, //    ######################## 
	0x0F, 0xFF, 0xFF, 0xC0, //     ######################  
	0x07, 0xFF, 0xFF, 0x80, //      ####################   
	0x01, 0xFF, 0xFF, 0x00, //        #################    
	0x00, 0x7F, 0xFC, 0x00, //          #############      
	0x00, 0x0F, 0xE0, 0x00, //             #######     
  0x00, 0x00, 0x00, 0x00,	
};

// 
//  Image data for wall
// 

const uint8_t wallBitMap[] =
{
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
	0x0F, 0xFE, // ########################
};

// 
//  Image data for ledge
// 

const uint8_t ledgeBitMap[] =
{
	0x7F, 0xFF, 0xFF, 0xFE, // ########################
	0x7F, 0xFF, 0xFF, 0xFE, // ########################
	0x7F, 0xFF, 0xFF, 0xFE, // ########################
	0x7F, 0xFF, 0xFF, 0xFE, // ########################
	0x7F, 0xFF, 0xFF, 0xFE, // ########################
	0x7F, 0xFF, 0xFF, 0xFE, // ########################
};

// 
//  Image data for ghost
//

const uint8_t ghostBitMap[] =
{
	0x00, 0x14, 0x00, //            # #         
	0x00, 0x3C, 0x00, //           ####         
	0x00, 0x2C, 0x00, //           # ##         
	0x00, 0x28, 0x00, //           # #          
	0x0F, 0x9B, 0x80, //     #####  ## ###      
	0x07, 0xFE, 0x80, //      ########## #            
	0x0F, 0x9B, 0x80, //     #####  ## ###      
	0x07, 0xFE, 0x80, //      ########## #      
	0x2D, 0xFF, 0xD8, //   # ## ########### ##  
	0x33, 0xFF, 0x60, //   ##  ########## ##    
	0x2D, 0xFF, 0x28, //   # ## #########  # #  
	0x0D, 0xFF, 0xE8, //     ## ############ #  
	0x1B, 0xFE, 0xF0, //    ## ######### ####   
	0x5B, 0xFE, 0xB4, //  # ## ######### # ## # 
	0x19, 0xFF, 0xB8, //    ##  ########## ###  
	0x53, 0xFF, 0x5C, //  # #  ########## # ### 
	0x47, 0x3A, 0xAC, //  #   ###  ### # # # ## 
	0x3B, 0x6D, 0x18, //   ### ## ## ## #   ##  
	0x5F, 0x5E, 0xF8, //  # ##### # #### #####  
	0x91, 0x82, 0xCA, // #  #   ##     # ##  # #
	0x3E, 0xFD, 0xA4, //   ##### ###### ## #  # 
	0x4C, 0x92, 0x36, //  #  ##  #  #  #   ## ##
	0x70, 0x14, 0x08, //  ###       # #      #  
	0xE0, 0x2C, 0x06, // ###       # ##       ##
	0xC0, 0x28, 0x04, // ##        # #        # 
	0x80, 0x18, 0x0A, // #          ##       # #
	0x40, 0x10, 0x0A, //  #         #        # #
	0xC0, 0x00, 0x00, // ##                     
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x10, 0x02, // #          #          #
	0x80, 0x08, 0x02, // #           #         #
	0x40, 0x08, 0x02, //  #          #         #
	0x40, 0x38, 0x04, //  #        ###        # 
	0xC0, 0x28, 0x02, // ##        # #         #
	0x6A, 0x6C, 0xDA, //  ## # #  ## ##  ## ## #
	0xE9, 0xFF, 0xE2, // ### #  ############   #
	0x6B, 0xFF, 0xE2, //  ## # #############   #
	0x6B, 0xFF, 0xE6, //  ## # #############  ##
	0x6B, 0xFF, 0xF6, //  ## # ############## ##
	0x6B, 0xFF, 0xFE, //  ## # #################
	0xEB, 0xFF, 0xFE, // ### # #################
	0xCB, 0xFF, 0xFE, // ##  # #################
	0xCF, 0xFF, 0xFE, // ##  ###################
	0xEC, 0x93, 0xEE, // ### ##  #  #  ##### ###
	0xCA, 0xD4, 0x9C, // ##  # # ## # #  #  ### 
	0xC3, 0xEC, 0x90, // ##    ##### ##  #  #   
	0x71, 0x83, 0x00, //  ###   ##     ##       
	0x30, 0x83, 0x08, //   ##    #     ##    #  
	0x20, 0x80, 0x0C, //   #     #           ## 
	0x20, 0x00, 0x0C, //   #                 ## 
	0x30, 0x03, 0x0C, //   ##          ##    ## 
	0x70, 0x03, 0x0C, //  ###          ##    ## 
};

// 
//  Image data for flag
// 

const uint8_t flagBitMap[] =
{
	0x7F, 0x00, 0x00, //  ##                   
	0x7F, 0xF0, 0x00, //    ## ##              
	0x7F, 0xFF, 0x00, // ###  # # # ##         
	0x7F, 0xFF, 0xF0, //  #  # ## ## # ## #    
	0x7F, 0xFF, 0xFE, // ## # # ### ###  # # ##
	0x7F, 0xFF, 0xF0, //  # ## ##  ## # ##     
	0x7F, 0xFF, 0x00, // # # # # ## #          
	0x7F, 0xF0, 0x00, // # #  #  #             
	0x7F, 0x00, 0x00, // ## ## 
	0x7F, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
	0x70, 0x00, 0x00,
};

// 
//  Image data for ground
// 

const uint8_t groundBitMap[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 
//  Image data for pacman ducking
// 

const uint8_t pacmanDuckBitMap[] =
{
	0x00, 0x00, 0x00, 0x00, //                      
	0x00, 0x0F, 0xE0, 0x00, //             #######          
	0x01, 0xFF, 0xFF, 0x00, //        #################    
	0x0F, 0xFF, 0xFF, 0xC0, //     ######################  
	0x1F, 0xFF, 0xFF, 0xF0, //    #########################
	0x7F, 0xFB, 0xFF, 0xC0, //  ############ ############  
	0x7F, 0xFF, 0xFF, 0x80, //  ########################    
	0xFF, 0xFF, 0xFC, 0x00, // ######################      
	0xFF, 0xFF, 0xE0, 0x00, // ###################         
	0xFF, 0xFF, 0xF8, 0x00, // #####################       
	0x7F, 0xFF, 0xFF, 0x00, //  #######################    
	0x7F, 0xFF, 0xFF, 0xE0, //  ########################## 
	0x1F, 0xFF, 0xFF, 0xF0, //    #########################
	0x0F, 0xFF, 0xFF, 0xC0, //     ######################   
	0x01, 0xFF, 0xFF, 0x00, //        #################    
	0x00, 0x0F, 0xE0, 0x00, //             #######     
  0x00, 0x00, 0x00, 0x00,	
};









