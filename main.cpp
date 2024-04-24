#include <iostream>

class Engine{
public:
    Engine(const double& capacity,const int& hp) : m_engineCapacity(capacity),m_hp(hp)
    {
    }

    Engine()
    {
    }

    Engine& operator =(const Engine& obj){
        if (this != &obj)
        {
            m_engineCapacity = obj.m_engineCapacity;
            m_hp = obj.m_hp;
        }

        return *this;
        
    }

    ~Engine()
    {
    }

public:
    void printEngine()
    {
       std::cout<<m_engineCapacity<<std::endl;
       std::cout<<m_hp<<std::endl;
    }

    void setCap(const double& cap)
    {
        m_engineCapacity = cap;
    }

    void setHp(const int& hp)
    {
        m_hp = hp;
    }
    
    double getCap() const
    {
        return m_engineCapacity;
    }

    int getHp() const
    {
        return m_hp;
    }
private:
    double m_engineCapacity = 0;
    int m_hp = 0;
};


class Car{
public:
    Car(const std::string& model,const std::string& make,const std::string& color,const int& year)
       : m_model(model),m_make(make),m_color(color),m_year(year)
    {
    }

    Car()
    {
    }

    Car& operator =(const Car& obj)
    {
             if (this != &obj)
             {
                m_model = obj.m_model;
                m_make = obj.m_make;
                m_color = obj.m_color;
                m_year = obj.m_year;
                m_engine.setCap(obj.m_engine.getCap());
                m_engine.setHp(obj.m_engine.getHp());
             }

             return *this;
             
    }   

    ~Car()
    {
        
    }

public:
void printCar()
{
    std::cout<<m_model<<std::endl;
    std::cout<<m_make<<std::endl;
    std::cout<<m_color<<std::endl;
    std::cout<<m_year<<std::endl;
    m_engine.printEngine();
}   

void setEngine(const Engine& obj){
    m_engine.setCap(obj.getCap());
    m_engine.setHp(obj.getHp());

}

private:
    std::string m_model;
    std::string m_make;
    std::string m_color;
    int m_year = 0;
    Engine m_engine;
};

class Parking{
public:
Parking(const int& size) : m_size(size)
{
    m_p = new Car[m_size];
    m_occupiedLots = new bool[m_size];

    for (int i = 0; i < m_size; ++i)
    {
        m_occupiedLots[i] = true;
    }
    
}

Parking& operator=(const Parking& obj)
{  
        if (this != &obj)
        {
            delete [] m_p;

            m_size = obj.m_size;
            m_occupied = obj.m_occupied;

            m_p = new Car[m_size];
            for (int i = 0; i < m_size; ++i)
            {
                if (!m_occupiedLots[i])
                {
                    m_p[i] = obj.m_p[i];
                }
                
            }
            
        }

        return *this; 
}

~Parking(){
    delete [] m_p;
    m_p = nullptr;

    delete [] m_occupiedLots;
    m_occupiedLots = nullptr;
}

public:
void registerCar(const Car& obj){
    if (m_occupied != m_size)
    {
         std::cout<<"Free lots:"<<std::endl;
         for (int i = 0; i < m_size; ++i)
         {
            if (m_occupiedLots[i])
            {
                std::cout<<i<<" ";
            }
         }

         std::cout<<std::endl;

         int lot = 0;
         std::cin>>lot;

         m_p[lot] = obj;
         ++m_occupied;
         m_occupiedLots[lot] = false;

    }
    else
    {
        std::cout<<"There is no free lot."<<std::endl;
    }
}

void toFreeTheLot(const int& index)
{
    if (!m_occupiedLots[index])
    {
        m_occupiedLots[index] = true;
    }
    else
    {
        std::cout<<"The lot is free:"<<std::endl;
    }
    
}

void printOccupiedLots()
{
    for (int i = 0; i < m_size; ++i)
    {
        if (!m_occupiedLots[i])
        {  
           std::cout<<"Lot's index: "<<i<<std::endl;
           m_p[i].printCar();
           std::cout<<std::endl;
        }
     
    }   
}

private:
  int m_size = 0;
  int m_occupied = 0;
  Car* m_p = nullptr;
  bool* m_occupiedLots = nullptr;  // False if the lot is occupied,True if the lot is free.

};
    
int main(int argc,char* argv[])
{
    int size = 4;

    Parking parking(4);

    Engine eM4(3.0,500);
    Car bmw("BMW","M4","Green",2022);
    bmw.setEngine(eM4);


    Engine eMB(3.0,300);
    Car mb("Mercedes - Benz","E-class","White",2019);
    mb.setEngine(eMB);
    mb.printCar();

    parking.registerCar(bmw);
    parking.registerCar(mb);

    parking.printOccupiedLots();

    parking.toFreeTheLot(1);

    parking.printOccupiedLots();

    return 0;
}
