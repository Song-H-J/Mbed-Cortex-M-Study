#ifndef _filters_h // 만약 필터가 정의되자 않았다면 정의한다.
#define _filters_h
template <typename T>
class LPFilter{
public:
    LPFilter<T>(float cutoffFreq, float dt){
        float Tconst=1.0f/(2*cutoffFreq*PI);
        alpha=exp(-dt/Tconst);
        beta=1-alpha;
    }

    T apply(T sample){
        _lastOut=alpha*_lastOut+beta*sample;
        return _lastOut;
    }
    
T getAlpha(){return alpha;}
  private:
    float alpha, beta;
    T _lastOut;
};
#endif