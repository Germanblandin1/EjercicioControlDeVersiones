
class Version{
    private:
        tm * timestap;
        int number;

    public:
        Version(){
            number=0;
            timestap=NULL;
        }

        Version(tm * p_timestap,int p_number){
            timestap = p_timestap;
            number=p_number;
        }

        int getNumber(){
            return number;
        }

        tm * getTimestap(){
            return timestap;
        }
};