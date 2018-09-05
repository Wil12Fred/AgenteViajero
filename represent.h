struct Represent{
    vector <int> ciudades;
    Represent (){}
    Represent (int b){
        ciudades.resize(b);
    }
    Represent operator = (const Represent& B){
	ciudades.resize((int)B.ciudades.size());
        for (int i = 0 ; i < ciudades.size(); i++){
            ciudades[i]= B.ciudades[i];
        }
        return (*this);
    }
    int tamano()const{
        return ciudades.size();
    }
    bool operator == (const Represent B)const{
        int i = 0;
        while (i < ciudades.size()){
            if (ciudades[i] != B.ciudades[i]){
                return false;
            }
        }
	return true;
    }
    bool operator < (const Represent B)const{
        int i = 0;
        while (i < ciudades.size()){
            if (ciudades[i]< B.ciudades[i]){
                return true;
	    } else if (ciudades[i]!=B.ciudades[i]){
		return false;
            }
	    i++;
       	}
	return false;
    }
};
