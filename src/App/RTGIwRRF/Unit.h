#ifndef _APP_RTGI_WITH_RRF_UNIT_H_
#define _APP_RTGI_WITH_RRF_UNIT_H_

#include <CppUtil/Basic/HeapObj.h>

#include <3rdParty/enum.h>

#include <vector>
#include <string>

namespace App {
	class Layer;

	class Unit : public CppUtil::Basic::HeapObj<Unit> {
	public:
		explicit Unit(CppUtil::Basic::CPtr<Layer> layer = nullptr,
			const std::vector<float> & weights = std::vector<float>())
			: layer(layer), weights(weights) { }

	public:
		static const CppUtil::Basic::Ptr<Unit> New(CppUtil::Basic::CPtr<Layer> layer = nullptr,
			const std::vector<float> & weights = std::vector<float>()) {
			return CppUtil::Basic::New<Unit>(layer, weights);
		}

	protected:
		virtual ~Unit() = default;

	public:
		int GetInputDim() const { return static_cast<int>(weights.size()) - 1; }
		const std::vector<float> & GetWeights() const { return weights; }
		const std::string GetFuncName() const;
		int GetID() const;
		const CppUtil::Basic::CPtr<Layer> GetLayer() const { return layer.lock(); }
		bool SetLayer(CppUtil::Basic::CPtr<Layer> layer) const;
		bool IsValid() const;

	public:
		const std::string GenComputeExpr() const;

	private:
		virtual void Init() override;

	private:
		mutable CppUtil::Basic::WCPtr<Layer> layer;
		std::vector<float> weights;
	};
}

#endif//!_APP_RTGI_WITH_RRF_UNIT_H_
