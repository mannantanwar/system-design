package ProxyDP21;

abstract class IDataFetcher{
    abstract void fetchData();
}

class RealDataFetcher extends IDataFetcher{
    @Override
    public void fetchData(){
        System.out.println("fetching the data by doing a lot of expensive crud operations");
    }
}
class ProxyDataFetcher extends IDataFetcher{
    private RealDataFetcher realDataFetcher;
    ProxyDataFetcher(){
        realDataFetcher = null; // lazy loading over hehre the object will be assigned only when it is needed just to avoid the cost of the expensive operation involved when the constructor of the reak data fetcher is called 
    }
    @Override 
    public void fetchData(){
        if(realDataFetcher==null){
            realDataFetcher= new RealDataFetcher();
        }
        System.out.println("fetching the data frpm the real data fetcher through the proxy service");
        realDataFetcher.fetchData();
    }
}
public class RemoteProxy {
    public static void main(String[] args) {
        IDataFetcher fetcher = new ProxyDataFetcher();
        fetcher.fetchData();
    }
}
