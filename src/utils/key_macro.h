/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_macro.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:37:47 by awillems          #+#    #+#             */
/*   Updated: 2022/12/20 15:10:24 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_MACRO_H
# define KEY_MACRO_H

//================================================//

# ifndef KEY_X11
#  define KEY_A		0
#  define KEY_B		11
#  define KEY_C		8
#  define KEY_D		2
#  define KEY_E		14
#  define KEY_F		3
#  define KEY_G		5
#  define KEY_H		4
#  define KEY_I		34
#  define KEY_J		38
#  define KEY_K		40
#  define KEY_L		37
#  define KEY_M		46
#  define KEY_N		45
#  define KEY_O		31
#  define KEY_P		35
#  define KEY_Q		12
#  define KEY_R		15
#  define KEY_S		1
#  define KEY_T		17
#  define KEY_U		32
#  define KEY_V		9
#  define KEY_W		13
#  define KEY_X		7
#  define KEY_Y		16
#  define KEY_Z		6

#  define KEY_1		18
#  define KEY_2		19
#  define KEY_3		20
#  define KEY_4		21
#  define KEY_5		23
#  define KEY_6		22
#  define KEY_7		26
#  define KEY_8		28
#  define KEY_9		25
#  define KEY_0		29

#  define KEY_NUM_1	83
#  define KEY_NUM_2	84
#  define KEY_NUM_3	85
#  define KEY_NUM_4	86
#  define KEY_NUM_5	87
#  define KEY_NUM_6	88
#  define KEY_NUM_7	89
#  define KEY_NUM_8	91
#  define KEY_NUM_9	92
#  define KEY_NUM_0	82

#  define KEY_SPACE	49

#  define KEY_TAB		48
#  define KEY_ENTER		48
#  define KEY_LSHIFT		257
#  define KEY_RSHIFT		258
#  define KEY_LCTRL		260
#  define KEY_RCTRL		259
#  define KEY_ALT		261
#  define KEY_ALT_GR		262
#  define KEY_BACKSPACE	51
#  define KEY_ESCAPE		53

#  define KEY_ARROW_UP		126
#  define KEY_ARROW_DOWN		125
#  define KEY_ARROW_RIGHT	124
#  define KEY_ARROW_LEFT		123
# endif /* KEY_X11 */

# ifdef KEY_X11
#  define KEY_1				0x0030  /* U+0030 DIGIT ZERO */
#  define KEY_2				0x0031  /* U+0031 DIGIT ONE */
#  define KEY_3				0x0032  /* U+0032 DIGIT TWO */
#  define KEY_4				0x0033  /* U+0033 DIGIT THREE */
#  define KEY_5				0x0034  /* U+0034 DIGIT FOUR */
#  define KEY_6				0x0035  /* U+0035 DIGIT FIVE */
#  define KEY_7				0x0036  /* U+0036 DIGIT SIX */
#  define KEY_8				0x0037  /* U+0037 DIGIT SEVEN */
#  define KEY_9				0x0038  /* U+0038 DIGIT EIGHT */
#  define KEY_0				0x0039  /* U+0039 DIGIT NINE */
#  define KEY_A				0x0061  /* U+0061 LATIN SMALL LETTER A */
#  define KEY_B				0x0062  /* U+0062 LATIN SMALL LETTER B */
#  define KEY_C				0x0063  /* U+0063 LATIN SMALL LETTER C */
#  define KEY_D				0x0064  /* U+0064 LATIN SMALL LETTER D */
#  define KEY_E				0x0065  /* U+0065 LATIN SMALL LETTER E */
#  define KEY_F				0x0066  /* U+0066 LATIN SMALL LETTER F */
#  define KEY_G				0x0067  /* U+0067 LATIN SMALL LETTER G */
#  define KEY_H				0x0068  /* U+0068 LATIN SMALL LETTER H */
#  define KEY_I				0x0069  /* U+0069 LATIN SMALL LETTER I */
#  define KEY_J				0x006a  /* U+006A LATIN SMALL LETTER J */
#  define KEY_K				0x006b  /* U+006B LATIN SMALL LETTER K */
#  define KEY_L				0x006c  /* U+006C LATIN SMALL LETTER L */
#  define KEY_M				0x006d  /* U+006D LATIN SMALL LETTER M */
#  define KEY_N				0x006e  /* U+006E LATIN SMALL LETTER N */
#  define KEY_O				0x006f  /* U+006F LATIN SMALL LETTER O */
#  define KEY_P				0x0070  /* U+0070 LATIN SMALL LETTER P */
#  define KEY_Q				0x0071  /* U+0071 LATIN SMALL LETTER Q */
#  define KEY_R				0x0072  /* U+0072 LATIN SMALL LETTER R */
#  define KEY_S				0x0073  /* U+0073 LATIN SMALL LETTER S */
#  define KEY_T				0x0074  /* U+0074 LATIN SMALL LETTER T */
#  define KEY_U				0x0075  /* U+0075 LATIN SMALL LETTER U */
#  define KEY_V				0x0076  /* U+0076 LATIN SMALL LETTER V */
#  define KEY_W				0x0077  /* U+0077 LATIN SMALL LETTER W */
#  define KEY_X				0x0078  /* U+0078 LATIN SMALL LETTER X */
#  define KEY_Y				0x0079  /* U+0079 LATIN SMALL LETTER Y */
#  define KEY_Z				0x007a  /* U+007A LATIN SMALL LETTER Z */
#  define KEY_ARROW_LEFT	0xff51  /* Move left, left arrow */
#  define KEY_ARROW_UP		0xff52  /* Move up, up arrow */
#  define KEY_ARROW_RIGHT	0xff53  /* Move right, right arrow */
#  define KEY_ARROW_DOWN	0xff54  /* Move down, down arrow */
#  define KEY_ESCAPE		0xff1b
# endif /* KEY_X11 */

//================================================//

#endif