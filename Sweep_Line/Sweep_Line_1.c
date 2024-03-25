//========================扫线=====================//
//void Sweep_Line(uint8 binaryzation_image[MT9V03X_H][MT9V03X_W])
//
//================================================//
uint8 midline[MT9V03X_H], leftline[MT9V03X_H], rightline[MT9V03X_H];

void Sweep_Line_Old(uint8 binaryzation_image[MT9V03X_H][MT9V03X_W])
{
	for (uint8 i = MT9V03X_H - 1; i > 0; i --) 		midline[i] = MT9V03X_W / 2;
	for (uint8 i = MT9V03X_H - 1; i > 0; i --){
		for (uint8 j = midline[i]; j >= 0; j--){
			if (binaryzation_image[i][j] == 0 || j == 0){
				leftline[i] = j;
				break;
			}
		}
		for (uint8 j = midline[i]; j < MT9V03X_W; j ++){
			if (binaryzation_image[i][j] == 0; || j == MT9V03X_W - 1){
				rightline[i] = j;
				break;
			}
		}
		midline[i] = (leftline[i] + rightline[i]) / 2;		//根据边线重置中线的值、
		if (binaryzation_image[i][midline[i]] == 0 || i == 0){
			midline[j] = midline[i];
			leftline[j] = leftline[i];
			rightline[j] = rightline[i];
		}
	}
}
void Sweep_Line(uint8 binaryzation_image[MT9V03X_H][MT9V03X_W])
{
	uint8 left_point = 1;
	uint8 right_point = MT9V03X_W - 1;
	uint8 mid_point = MT9V03X_W / 2;

	for (uint8 i = MT9V03X_H - 1; i > 0; i ++){
		if (binaryzation_image[i][mid_point] == 255){
			for (uint8 j = mid_point; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					break;
				}
			}
			for (uint8 j = mid_point; j < MT9V03X_W; j ++){
				if (binaryzation_image[i][j] == 0; && binaryzation_image[i][j - 1] == 255){
					right_point == j;
					break;
				}
			}
		}
		else if (binaryzation_image[i][mid_point / 2] == 255){
			for (uint8 j = mid_point / 2; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					break;
				}
			}
			for (uint8 j = mid_point / 2; j < MT9V03X_W - 1; j ++){
				if (binaryzation_image[i][j] == 0; && binaryzation_image[i][j - 1] == 255){
					right_point == j;
					break;
				}
			}
		}
		else if (binaryzation_image[i][mid_point / 2 * 3] == 255){
			for (uint8 j = mid_point / 2 * 3; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					break;
				}
			}
			for (uint8 j = mid_point / 2 * 3; j < MT9V03X_W - 1; j ++){
				if (binaryzation_image[i][j] == 0; && binaryzation_image[i][j - 1] == 255){
					right_point == j;
					break;
				}
			}
		}
	}
}

