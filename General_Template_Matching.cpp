#include Matching.h

bool MatchTemplate(const unsigned char* pSource, unsigned nImageWidth, unsigned nImageHeight, const unsigned char* pTemplate,
		unsigned nTplWidth, unsigned nTplHeight, PointVector& Result){
		
	float global_max = 0;
	float* filteredR;
	filteredR = (float*) malloc(sizeof(float)*nImageWidth*nImageHeight);
	
	for(unsigned y = 0; y < nImageHeight; y++){
		for(unsigned x = 0; x < nImageWidth; x++){
			filteredR[y*nImageWidth + x] = 0;
			if(pSource[y*nImageWidth + x] == 0){} // no need to convolve pixel 
			else{
				for(unsigned y_del = 0; y_del < nTplHeight; y_del++){
					for(unsigned x_del = 0; x_del < nTplWidth; x_del++){
						if((x + x_del - 3) < 0 || (y + y_del - 4) < 0){} //pixel out of scope
						else{
							filteredR[y*nImageWidth + x] += (1/256) * (float)(pSource[(y + y_del - 4)*nImageWidth + (x + x_del -3)]) * (float)(pTemplate[y_del*nTplWidth + x_del]);
							}
					}
				}
			}
			if(filteredR[y*nImageWidth + x] > global_max) global_max = filteredR[y*nImageWidth + x]; // determine global_max
		}
	}
		for(unsigned y = 0; y < nImageHeight; y++){
			for(unsigned x = 0; x < nImageWidth; x++){
				if(filteredR[y*nImageWidth + x] >= global_max * 0.95f){
					Result.push_back(std::make_pair(x,y));
				}
			}
		}
	free((float*)filteredR);
	return true;
}