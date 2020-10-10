#pragma once


class PhysicalLogic;
class Composition;


class PhysicsSerializer
{
public:
	virtual PhysicalLogic* Create() = 0;
};

template< class Type >
class PhysicsSerializerType : public PhysicsSerializer
{
public:
	virtual PhysicalLogic* Create() { return new Type; }
};


class PhysicalLogic
{
public:
	PhysicalLogic( ) { }
	virtual ~PhysicalLogic() { }

	virtual void Execute( int dt ) = 0;
	virtual void Initialize( Composition* owner ) = 0;
	virtual PhysicalLogic* Clone() = 0;
	
protected:
};
