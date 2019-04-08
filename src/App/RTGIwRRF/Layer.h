#ifndef _APP_RTGI_WITH_RRF_LAYER_H_
#define _APP_RTGI_WITH_RRF_LAYER_H_

#include <CppUtil/Basic/HeapObj.h>

#include <3rdParty/enum.h>

#include <vector>
#include <string>

namespace App {
	class Model;
	class Unit;

	BETTER_ENUM(Connection, int,
		Dense)

	BETTER_ENUM(Activation, int,
		Identity,
		ReLU,
		tanh)

	class Layer : public CppUtil::Basic::HeapObj<Layer> {
	public:
		explicit Layer(CppUtil::Basic::CPtr<Model> model = nullptr,
			const int inputDim = -1,
			const Connection & connection = Connection::Dense,
			const Activation & activation = Activation::Identity)
			: model(model), inputDim(inputDim), connection(connection), activation(activation) { }

	public:
		static const CppUtil::Basic::Ptr<Layer> New(CppUtil::Basic::CPtr<Model> model = nullptr,
			const int inputDim = -1,
			const Connection & connection = Connection::Dense,
			const Activation & activation = Activation::Identity)
		{
			return CppUtil::Basic::New<Layer>(model, inputDim, connection, activation);
		}

	protected:
		virtual ~Layer() = default;

	public:
		const std::vector<CppUtil::Basic::CPtr<Unit>> & GetUnits() const { return units; }
		const Activation & GetActivation() const { return activation; }
		const Connection & GetConnection() const { return connection; }
		int GetInputDim() const { return inputDim; }
		int GetOutputDim() const { return static_cast<int>(units.size()); }
		const CppUtil::Basic::CPtr<Model> GetModel() const { return model.lock(); }
		bool SetModel(CppUtil::Basic::CPtr<Model> model) const;

		int GetIDof(CppUtil::Basic::CPtr<Unit> unit) const;
		int GetID() const;
		const std::string GetFuncName() const;
		
		bool IsValid() const;

	public:
		bool AddUnit(CppUtil::Basic::CPtr<Unit> unit) const;
		const std::string GenFunc(bool genUnits = true) const;

	private:
		virtual void Init() override;

	private:
		mutable CppUtil::Basic::WCPtr<Model> model;
		mutable std::vector<CppUtil::Basic::CPtr<Unit>> units;

		int inputDim;
		Connection connection;
		Activation activation;
	};
}

#endif//!_APP_RTGI_WITH_RRF_LAYER_H_
