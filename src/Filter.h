#pragma once

class Filter{
protected:
	// データ遅れ
	enum enDELAY{
		DELAY_0 = 0,
		DELAY_1,
		DELAY_2,
		DELAY_MAX
	};

	unsigned int time_ms;		// サンプリング間隔[ms]
	double	cutoffFre;			// 折点角周波数

	double	input[DELAY_MAX];	// 入力値
	double	output[DELAY_MAX];	// 出力値

	// ２乗
	template<class T>
	inline T square(const T& x){
		return ((x)*(x));
	}

public:
	explicit Filter(unsigned int t, const double &cutoff);
	virtual ~Filter(){};
	virtual double filtering(const double&) = 0;
};

//------------------------------------------//
// JAXAのフィルタ							//
//------------------------------------------//
// Translationのハイパスフィルタ
class JAXA_tHPF : public Filter{
public:
	// コンストラクタ
	explicit JAXA_tHPF(unsigned int t_ms, const double &cutoff)
		: Filter(t_ms, cutoff){};

	// フィルタリング
	double filtering(const double&);
};

// Tilt-Coordinationのローパスフィルタ
class JAXA_tLPF : public Filter{
private:
	// ダンピング係数
	double damp;

public:
	// コンストラクタ
	explicit JAXA_tLPF(unsigned int t_ms, const double &cutoff, const double &dmp)
		: Filter(t_ms, cutoff), damp(dmp){};

	// フィルタリング
	double filtering(const double&);
};

// Rotationのハイパスフィルタ
class JAXA_rHPF : public Filter{
public:
	// コンストラクタ
	explicit JAXA_rHPF(unsigned int t_ms, const double &cutoff)
		: Filter(t_ms, cutoff){};

	// フィルタリング
	double filtering(const double&);
};
