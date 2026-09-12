package ZeptoSystemDesign;

import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Set;
import java.util.TreeSet;
import java.util.Comparator;

class Product {
    private int sku;
    private String name;
    private double price;

    Product(String name, int sku, double price) {
        this.name = name;
        this.sku = sku;
        this.price = price;
    }

    public int getSku() {
        return sku;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }
}

// now making the porduct factory class
class ProductFactory {
    public Product createProduct(String name, int sku, double price) {
        return new Product(name, sku, price);
    }
}

// now making the inventory which will be storing the products and add and
// rmeove operation on the inventory stock
abstract class InventoryStore {
    abstract public void addProducts(Product product, int qty);

    abstract public void removeProducts(Product product, int qty);

    abstract public List<Product> listAll();

    abstract public int checkStock(long sku);
    abstract void addStock(int sku , int qty);
    abstract void removeStock (int sku , int qty);
}

// concrete InventoryStore - nothing implemented this before, so every IventoryManager's
// `inventory` field was always null and any add/remove/checkStock call would NPE at runtime.
// NOTE: addStock(sku, qty) only ever receives a bare sku, with no name/price - if this is
// the first time that sku is seen, a placeholder Product is created (name "Product<sku>",
// price 0.0). Use addProducts(Product, qty) directly instead if you need real name/price data.
class SimpleInventoryStore extends InventoryStore {
    private Map<Integer, Integer> stock = new HashMap<>();
    private Map<Integer, Product> products = new HashMap<>();

    @Override
    public void addProducts(Product product, int qty) {
        products.put(product.getSku(), product);
        stock.merge(product.getSku(), qty, Integer::sum);
    }

    @Override
    public void removeProducts(Product product, int qty) {
        stock.merge(product.getSku(), -qty, Integer::sum);
    }

    @Override
    public List<Product> listAll() {
        return new ArrayList<>(products.values());
    }

    @Override
    public int checkStock(long sku) {
        return stock.getOrDefault((int) sku, 0);
    }

    @Override
    void addStock(int sku, int qty) {
        products.computeIfAbsent(sku, s -> new Product("Product" + s, s, 0.0));
        stock.merge(sku, qty, Integer::sum);
    }

    @Override
    void removeStock(int sku, int qty) {
        stock.merge(sku, -qty, Integer::sum);
    }
}

// now making the inventory manager ps not making this manager singleton as
// there can be a lot of inventories depending upon the regio and each invertory
// should have its own manager
public class IventoryManager {
    private InventoryStore inventory;

    public IventoryManager() {
        this.inventory = new SimpleInventoryStore();
    }

    public void addStock(Map<Product, Integer> mp) {
        for (Map.Entry<Product, Integer> entry : mp.entrySet()) {
            inventory.addProducts(entry.getKey(), entry.getValue());
        }
    }

    public void removeStock(Map<Product, Integer> mp) {
        for (Map.Entry<Product, Integer> entry : mp.entrySet()) {
            inventory.removeProducts(entry.getKey(), entry.getValue());
        }
    }

    public int checkStock(int sku) {
        return inventory.checkStock(sku);
    }

    public List<Product> getAvailableProducts() {
        return inventory.listAll();
    }

    public void removeStock(int sku, int qty) {
        inventory.removeStock(sku, qty);
    }

    public void addStock(int sku, int qty) {
        inventory.addStock(sku, qty);
    }

}

// there can by refilling strategies sho now making that using factory design
// pattern
abstract class RefillStrategy {
    public abstract void refill(IventoryManager manager, Map<Product, Integer> mp);
}

class ThresholdRefillStrategy extends RefillStrategy {
    private int threshold;

    ThresholdRefillStrategy(int threshold) {
        this.threshold = threshold;
    }

    @Override
    public void refill(IventoryManager manager, Map<Product, Integer> mp) {
        // if quantity threshold se less then only refill else not
        Map<Product, Integer> refillMap = new HashMap<>();
        for (Map.Entry<Product, Integer> entry : mp.entrySet()) {
            if (entry.getValue() < threshold) {
                refillMap.put(entry.getKey(), threshold - entry.getValue());
            }
        }
        manager.addStock(refillMap);
    }
}

class WeeklyRefillStrategy extends RefillStrategy {

    @Override
    public void refill(IventoryManager manager, Map<Product, Integer> mp) {
        // weekly refill: unconditionally restock every product with the given quantity
        manager.addStock(mp);
    }
}

// now time for tha dark store
class DarkStore {
    private String name;
    private double x;
    private double y;
    private IventoryManager inventoryManager;
    private RefillStrategy refillStrategy;

    DarkStore(String name, double x, double y, IventoryManager inventoryManager) {
        this.name = name;
        this.x = x;
        this.y = y;
        this.inventoryManager = inventoryManager;
    }

    DarkStore(String name, double x, double y) {
        this(name, x, y, new IventoryManager());
    }

    public List<Product> getAllProducts() {
        return inventoryManager.getAvailableProducts();
    }

    public void setStrategy(RefillStrategy strategy) {
        this.refillStrategy = strategy;
    }

    public void runReplenish(Map<Product, Integer> mp) {
        refillStrategy.refill(inventoryManager, mp);
    }

    public String getName() {
        return name;
    }

    public double getDistance(double xu, double yu) {
        return Math.sqrt((xu - x) * (xu - x) + (yu - y) * (yu - y));
    }

    public int checkStock(int sku) {
        return inventoryManager.checkStock(sku);
    }

    public IventoryManager getInventoryManager() {
        return inventoryManager;
    }
   public void removeStock(int sku, int qty) {
        inventoryManager.removeStock(sku, qty);
    }

    public void addStock(int sku, int qty) {
        inventoryManager.addStock(sku, qty);
    }
}

// helper class of teh pair
class Pair<T, U> {
    private T first;
    private U second;

    Pair(T first, U second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return first;
    }

    public U getSecond() {
        return second;
    }
}

// have to make it singleton
class DarkStoreManager {
    private DarkStoreManager() {
        stores = new ArrayList<>();
    }

    private List<DarkStore> stores;
    private static DarkStoreManager instance;

    public static DarkStoreManager getInstance() {
        if (instance == null)
            instance = new DarkStoreManager();
        return instance;
    }

    public void addStores(DarkStore store) {
        stores.add(store);
    }

    public List<DarkStore> getNearByStores(double x, double y, double maxDistance) {
        // TreeSet keeps entries sorted by distance as they're added - no separate sort
        // step needed.
        // Ties (same rounded distance) are broken by identity hash so two different
        // stores never
        // get treated as "equal" and silently dropped by the Set.
        Set<Pair<Integer, DarkStore>> nearbyStores = new TreeSet<>(
                Comparator.<Pair<Integer, DarkStore>>comparingInt(Pair::getFirst)
                        .thenComparingInt(p -> System.identityHashCode(p.getSecond())));
        for (DarkStore st : stores) {
            double distance = st.getDistance(x, y);
            if (distance <= maxDistance) {
                nearbyStores.add(new Pair<>((int) distance, st));
            }
        }
        // nearbyStores is already sorted by distance (that's what the TreeSet does for
        // us)
        List<DarkStore> result = new ArrayList<>();
        for (Pair<Integer, DarkStore> pair : nearbyStores) {
            result.add(pair.getSecond());
        }
        return result;
    }
}

class Cart {
    private Map<Product, Integer> items = new HashMap<>();

    public void addItem(Product product, int qty) {
        items.put(product, qty);
    }

    // convenience overload for adding by bare sku - see SimpleInventoryStore's note
    // on placeholder Products for why this is imprecise (no real name/price available)
    public void addItem(int sku, int qty) {
        items.put(new Product("Product" + sku, sku, 0.0), qty);
    }

    public Map<Product, Integer> getItems() {
        return items;
    }

    public double getTotal() {
        double total = 0;
        for (Map.Entry<Product, Integer> entry : items.entrySet()) {
            total += entry.getKey().getPrice() * entry.getValue();
        }
        return total;
    }
}

class DeliveryPartner {
    DeliveryPartner(String name) {
        this.name = name;
    }

    private String name;

    public String getName() {
        return this.name;
    }
}

class User {
    private double x;
    private double y;
    private Cart cart;
    private String name;

    User(double x, double y, String name) {
        this.name = name;
        this.x = x;
        this.y = y;
        this.cart = new Cart();
    }

    public Pair<Double, Double> getLocation() {
        Pair<Double, Double> location = new Pair<>(x, y);
        return location;
    }

    public String getName() {
        return name;
    }

    public Cart getCart() {
        return cart;
    }
}

class Order {
    private static int nextId = 1;
    public int orderId;
    public User user;
    public List<Pair<Product, Integer>> items;
    public double totalAmount;
    // requirements me likha hai that if one dark store cannot process the order
    // then multiple delivery partner and the dark store can com ein the picture
    // but the quesition is how do i make an order split into two dark stores
    public List<DeliveryPartner> partners;

    Order(User user) {
        orderId = nextId++;
        totalAmount = 0;
        this.user = user;
        items = new ArrayList<>();
        partners = new ArrayList<>();
    }
}

class OrderManager {
    private static OrderManager instance;
    public DarkStoreManager darkStoreManager = DarkStoreManager.getInstance();
    private List<Order> orders = new ArrayList<>();

    public static OrderManager getInstance() {
        if (instance == null)
            instance = new OrderManager();
        return instance;
    }

    public void placeOrder(User user, Cart cart) {
        Map<Product, Integer> requestedItems = cart.getItems();
        // we have got the list of the items that have been requested to be ordered
        // now what we have to di is get all the dark stores nearby this user and check
        // that if we have tp get one dark stroe of mu;ltiple
        Pair<Double, Double> location = user.getLocation();
        double maxDistance = 5;
        List<DarkStore> nearbyStores = darkStoreManager.getNearByStores(location.getFirst(), location.getSecond(),
                maxDistance);

        DarkStore firstStore = nearbyStores.get(0);
        boolean allInFirst = true;
        for (Map.Entry<Product, Integer> item : requestedItems.entrySet()) {
            if (firstStore.checkStock(item.getKey().getSku()) < item.getValue()) {
                allInFirst = false;
                break;
            }
        }

        Order order = new Order(user);

        // One delivery partner required - a single dark store covers everything
        if (allInFirst) {
            System.out.println("  All items at: " + firstStore.getName());

            for (Map.Entry<Product, Integer> item : requestedItems.entrySet()) {
                int sku = item.getKey().getSku();
                int qty = item.getValue();
                firstStore.removeStock(sku, qty);
                order.items.add(new Pair<>(item.getKey(), qty));
            }

            order.totalAmount = cart.getTotal();
            order.partners.add(new DeliveryPartner("Partner1"));
            System.out.println("  Assigned Delivery Partner: Partner1");
        }
        // Multiple delivery partners required - split across stores
        else {
            System.out.println("  Splitting order across stores...");
            // keep the actual Product objects around (not just their skus) so we never
            // need to reconstruct one later
            Map<Product, Integer> remainingItems = new HashMap<>(requestedItems);

            int partnerId = 1;
            for (DarkStore store : nearbyStores) {
                if (remainingItems.isEmpty()) break;
                System.out.println("   Checking: " + store.getName());
                boolean suppliedByThisStore = false;
                List<Product> fulfilled = new ArrayList<>();
                for (Map.Entry<Product, Integer> entry : remainingItems.entrySet()) {
                    Product product = entry.getKey();
                    int sku = product.getSku();
                    int qtyNeeded = entry.getValue();
                    int availableQty = store.checkStock(sku);
                    if (availableQty <= 0) continue;
                    int takenQty = Math.min(availableQty, qtyNeeded);
                    store.removeStock(sku, takenQty);
                    System.out.println("     " + store.getName() + " supplies SKU " + sku
                                     + " x" + takenQty);
                    order.items.add(new Pair<>(product, takenQty));
                    suppliedByThisStore = true;
                    if (qtyNeeded > takenQty) {
                        entry.setValue(qtyNeeded - takenQty);
                    } else {
                        fulfilled.add(product);
                    }
                }
                for (Product product : fulfilled) {
                    remainingItems.remove(product);
                }
                if (suppliedByThisStore) {
                    String pname = "Partner" + partnerId++;
                    order.partners.add(new DeliveryPartner(pname));
                    System.out.println("     Assigned: " + pname + " for " + store.getName());
                }
            }
            if (!remainingItems.isEmpty()) {
                System.out.println("  Could not fulfill:");
                for (Map.Entry<Product, Integer> entry : remainingItems.entrySet()) {
                    System.out.println("    SKU " + entry.getKey().getSku()
                                     + " x" + entry.getValue());
                }
            }
            double sum = 0;
            for (Pair<Product, Integer> it : order.items) {
                sum += it.getFirst().getPrice() * it.getSecond();
            }
            order.totalAmount = sum;
        }

        // Printing Order Summary
        System.out.println("\n[OrderManager] Order #" + order.orderId + " Summary:");
        System.out.println("  User: " + user.getName() + "\n  Items:");
        for (Pair<Product, Integer> item : order.items) {
            System.out.println("    SKU " + item.getFirst().getSku()
                             + " (" + item.getFirst().getName() + ") x" + item.getSecond()
                             + " @ Rs " + item.getFirst().getPrice());
        }
        System.out.println("  Total: Rs " + order.totalAmount + "\n  Partners:");
        for (DeliveryPartner dp : order.partners) {
            System.out.println("    " + dp.getName());
        }
        System.out.println();

        orders.add(order);
    }
}

// Facade - gives client code (main, below) one simple entry point instead of making it
// juggle DarkStoreManager, DarkStore, RefillStrategy and Product directly
class ZeptoFacade {
    public static void showAllItems(User user) {
        System.out.println("\n[Zepto] All Available products within 5 KM for " + user.getName() + ":");
        DarkStoreManager dsManager = DarkStoreManager.getInstance();
        Pair<Double, Double> loc = user.getLocation();
        List<DarkStore> nearbyStores = dsManager.getNearByStores(loc.getFirst(), loc.getSecond(), 5.0);
        Map<Integer,Double> skuToPrice = new HashMap<>();
        Map<Integer,String>  skuToName  = new HashMap<>();

        for (DarkStore ds : nearbyStores) {
            for (Product product : ds.getAllProducts()) {
                int sku = product.getSku();
                if (!skuToPrice.containsKey(sku)) {
                    skuToPrice.put(sku, product.getPrice());
                    skuToName.put(sku, product.getName());
                }
            }
        }

        for (Map.Entry<Integer,Double> entry : skuToPrice.entrySet()) {
            System.out.println("  SKU " + entry.getKey() + " - "
                               + skuToName.get(entry.getKey())
                               + " @ Rs " + entry.getValue());
        }
    }

    public static void initialize() {
        DarkStoreManager dsManager = DarkStoreManager.getInstance();

        // DarkStore A.......
        DarkStore darkStoreA = new DarkStore("DarkStoreA", 0.0, 0.0);
        darkStoreA.setStrategy(new ThresholdRefillStrategy(3));
        System.out.println("\nAdding stocks in DarkStoreA....");
        darkStoreA.addStock(101, 5);
        darkStoreA.addStock(102, 2);

        // DarkStore B.......
        DarkStore darkStoreB = new DarkStore("DarkStoreB", 4.0, 1.0);
        darkStoreB.setStrategy(new ThresholdRefillStrategy(3));
        System.out.println("\nAdding stocks in DarkStoreB....");
        darkStoreB.addStock(101, 3);
        darkStoreB.addStock(103, 10);

        // DarkStore C.......
        DarkStore darkStoreC = new DarkStore("DarkStoreC", 2.0, 3.0);
        darkStoreC.setStrategy(new ThresholdRefillStrategy(3));
        System.out.println("\nAdding stocks in DarkStoreC....");
        darkStoreC.addStock(102, 5);
        darkStoreC.addStock(201, 7);

        dsManager.addStores(darkStoreA);
        dsManager.addStores(darkStoreB);
        dsManager.addStores(darkStoreC);
    }
}

class ZeptoSystemDesign {
    public static void main(String[] args) {
        // 1) Initialize.
        ZeptoFacade.initialize();

        // 2) A User comes on Platform
        User user = new User(1.0, 1.0, "Aditya");
        System.out.println("\nUser with name " + user.getName() + " comes on platform");

        // 3) Show all available items via Zepto
        ZeptoFacade.showAllItems(user);

        // 4) User adds items to cart
        System.out.println("\nAdding items to cart");
        Cart cart = user.getCart();
        cart.addItem(101, 4);
        cart.addItem(102, 3);
        cart.addItem(103, 2);

        // 5) Place Order
        OrderManager.getInstance().placeOrder(user, cart);

        System.out.println("\n=== Demo Complete ===");
    }
}
