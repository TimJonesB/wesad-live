
#include "header.h"

;


size_t get_num_class(void) {
  return 1;
}

size_t get_num_feature(void) {
  return 13;
}

const char* get_pred_transform(void) {
  return "sigmoid";
}

float get_sigmoid_alpha(void) {
  return 1.0;
}

float get_global_bias(void) {
  return -0.0;
}

const char* get_threshold_type(void) {
  return "float32";
}

const char* get_leaf_output_type(void) {
  return "float32";
}


static inline float pred_transform(float margin) {
  const float alpha = (float)1.0;
  return (float)(1) / ((float)(1) + expf(-alpha * margin));
}
float predict(union Entry* data, int pred_margin) {
  float sum = (float)0;
  unsigned int tmp;
  int nid, cond, fid;  /* used for folded subtrees */
  if (!(data[2].missing != -1) || (data[2].fvalue < (float)109.70139313)) {
    if (!(data[11].missing != -1) || (data[11].fvalue < (float)8.474146843)) {
      sum += (float)-1.7759679556;
    } else {
      sum += (float)0.35867106915;
    }
  } else {
    if (!(data[0].missing != -1) || (data[0].fvalue < (float)0.79928547144)) {
      sum += (float)1.2469068766;
    } else {
      sum += (float)-1.8915481567;
    }
  }
  if ( (data[11].missing != -1) && (data[11].fvalue < (float)0.98906862736)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < (float)120.30357361)) {
      sum += (float)-1.142521739;
    } else {
      sum += (float)0.14317379892;
    }
  } else {
    if (!(data[9].missing != -1) || (data[9].fvalue < (float)92.504203796)) {
      sum += (float)-0.57606637478;
    } else {
      sum += (float)1.834397912;
    }
  }
  if ( (data[7].missing != -1) && (data[7].fvalue < (float)8.7814884186)) {
    if ( (data[4].missing != -1) && (data[4].fvalue < (float)-0.0043015265837)) {
      sum += (float)1.8029565811;
    } else {
      sum += (float)-0.64586389065;
    }
  } else {
    if ( (data[12].missing != -1) && (data[12].fvalue < (float)33.420833588)) {
      sum += (float)0.0073311813176;
    } else {
      sum += (float)4.9094104767;
    }
  }
  if (!(data[9].missing != -1) || (data[9].fvalue < (float)87.504043579)) {
    if ( (data[12].missing != -1) && (data[12].fvalue < (float)34.220291138)) {
      sum += (float)-0.9529004693;
    } else {
      sum += (float)-4.5658364296;
    }
  } else {
    if (!(data[8].missing != -1) || (data[8].fvalue < (float)52.508335114)) {
      sum += (float)-0.38203468919;
    } else {
      sum += (float)1.2161527872;
    }
  }
  if (!(data[7].missing != -1) || (data[7].fvalue < (float)2.9159300327)) {
    if (!(data[11].missing != -1) || (data[11].fvalue < (float)1.6087177992)) {
      sum += (float)-1.3404145241;
    } else {
      sum += (float)-0.27852225304;
    }
  } else {
    if ( (data[2].missing != -1) && (data[2].fvalue < (float)82.74446106)) {
      sum += (float)-0.49500778317;
    } else {
      sum += (float)0.93218481541;
    }
  }
  if ( (data[1].missing != -1) && (data[1].fvalue < (float)0.13904190063)) {
    if (!(data[1].missing != -1) || (data[1].fvalue < (float)0.025221090764)) {
      sum += (float)-0.69087862968;
    } else {
      sum += (float)0.28715494275;
    }
  } else {
    if (!(data[4].missing != -1) || (data[4].fvalue < (float)-0.004008767195)) {
      sum += (float)-2.3319280148;
    } else {
      sum += (float)-1.0849388838;
    }
  }
  if ( (data[4].missing != -1) && (data[4].fvalue < (float)-0.0028405019548)) {
    if (!(data[2].missing != -1) || (data[2].fvalue < (float)99.042572021)) {
      sum += (float)-0.67513370514;
    } else {
      sum += (float)0.39353305101;
    }
  } else {
    if ( (data[7].missing != -1) && (data[7].fvalue < (float)3.0906996727)) {
      sum += (float)-0.30452424288;
    } else {
      sum += (float)2.4039797783;
    }
  }
  if (!(data[0].missing != -1) || (data[0].fvalue < (float)0.33984810114)) {
    if ( (data[0].missing != -1) && (data[0].fvalue < (float)0.0042579444125)) {
      sum += (float)-0.83024948835;
    } else {
      sum += (float)1.5654536486;
    }
  } else {
    if (!(data[11].missing != -1) || (data[11].fvalue < (float)13.802517891)) {
      sum += (float)-0.57553243637;
    } else {
      sum += (float)1.5907673836;
    }
  }
  if ( (data[11].missing != -1) && (data[11].fvalue < (float)1.2358920574)) {
    if (!(data[3].missing != -1) || (data[3].fvalue < (float)512.5)) {
      sum += (float)-0.24057915807;
    } else {
      sum += (float)-1.2241473198;
    }
  } else {
    if (!(data[10].missing != -1) || (data[10].fvalue < (float)42.692306519)) {
      sum += (float)2.0265161991;
    } else {
      sum += (float)0.075683169067;
    }
  }
  if ( (data[12].missing != -1) && (data[12].fvalue < (float)32.215000153)) {
    if ( (data[7].missing != -1) && (data[7].fvalue < (float)3.5196270943)) {
      sum += (float)0.14365501702;
    } else {
      sum += (float)-1.0013513565;
    }
  } else {
    if (!(data[12].missing != -1) || (data[12].fvalue < (float)33.881332397)) {
      sum += (float)0.45699089766;
    } else {
      sum += (float)-0.81978112459;
    }
  }

  sum = sum + (float)(-0);
  if (!pred_margin) {
    return pred_transform(sum);
  } else {
    return sum;
  }
}
