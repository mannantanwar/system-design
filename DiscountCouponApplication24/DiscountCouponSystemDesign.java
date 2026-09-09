package DiscountCouponApplication24;

import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
class Product{
    private String name;
    private String category ;
    private double price;
    Product(String name, String category , double price){
        this.name= name;
        this.category= category ;
        this.price = price;
    }
    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }
    public String getCategory(){
        return category;
    }
    public void setCategory(String category){
        this.category = category;
    }
    public double getPrice(){
        return price;
    }
    public void setPrice(double price){
        this.price = price;
    }
}

class CartItem{
    private int quantity;
    private Product product;
    CartItem(Product product , int quantity){
        this.product = product;
        this.quantity= quantity;
    }
    public Product getProduct(){
        return product;
    }
    public void setProduct(Product product){
        this.product = product;
    }
    public int getQuantity(){
        return quantity;
    }
    public void setQuantity(int quantity){
        this.quantity = quantity;
    }
    public double itemTotal(){
        return product.getPrice() * quantity;
    }
}

class Cart{
    private List<CartItem>products ;
    private double initialTotal;
    private double finalTotal;
    private boolean isLoayaltyMember;
    private String paymentBank;
    public void addProduct(Product product, int quantity){
        products.add(new CartItem(product, quantity));
    }
    public void applyDiscount(double amount){
        finalTotal-=amount;
    }
    public List<CartItem> getItems(){
        return products;
    }
    public boolean isLoyaltyMember(){
        return isLoayaltyMember;
    }
    public void setLoyaltyMember(boolean isLoayaltyMember){
        this.isLoayaltyMember = isLoayaltyMember;
    }
    public double getOriginalTotal(){
        return initialTotal;
    }
    public void setOriginalTotal(double initialTotal){
        this.initialTotal = initialTotal;
    }
    public double getCurrentTotal(){
        return finalTotal;
    }
    public void setCurrentTotal(double finalTotal){
        this.finalTotal = finalTotal;
    }
    public String getPaymentBank(){
        return paymentBank;
    }
    public void setPaymentBank(String paymentBank){
        this.paymentBank = paymentBank;
    }
}

abstract class DiscountStrategy{
    abstract double calculate(double amount);
}

class FlatDiscountStrategy extends DiscountStrategy{
    private double flat;
    FlatDiscountStrategy(double flat){
        this.flat = flat;
    }
    @Override
    double calculate(double amount){
        return amount - flat;
    }
}
class PercentDiscountStrategy extends DiscountStrategy{
    private double percent;
    PercentDiscountStrategy(double percent){
        this.percent = percent;
    }
    @Override
    double calculate(double amount){
        return amount - (amount *percent)/100;
    }
}
class PercentWithCapDiscountStrategy extends DiscountStrategy{
    private double cap;
    private double percent;
    PercentWithCapDiscountStrategy(double cap , double percent){
        this.percent = percent;
        this.cap = cap;
    }
    @Override
    double calculate(double amount){
        if((amount*percent)/100  >= cap){
            return amount- cap;
        }
        else return amount - (amount *percent)/100;
    }
}
enum StrategyType {
    FLAT,
    PERCENT,
    PERCENT_WITH_CAP
}

// ----------------------------
// DiscountStrategyManager (Singleton)
// ----------------------------
class DiscountStrategyManager {
    private static DiscountStrategyManager instance;

    private DiscountStrategyManager() {}

    public static synchronized DiscountStrategyManager getInstance() {
        if (instance == null) {
            instance = new DiscountStrategyManager();
        }
        return instance;
    }

    public DiscountStrategy getStrategy(StrategyType type, double param1, double param2) {
        switch(type) {
            case FLAT:
                return new FlatDiscountStrategy(param1);
            case PERCENT:
                return new PercentDiscountStrategy(param1);
            case PERCENT_WITH_CAP:
                return new PercentWithCapDiscountStrategy(param1, param2);
            default:
                return null;
        }
    }
}

// can fllow the chain or responsobility DP here as the coupons can be appliedin the chain here so might use thedecorator DP or cna also use the COR DP here
abstract class Coupon {
    private Coupon next ;
    private DiscountStrategy discountStrategy;
    public void applyDiscount(Cart cart){
        if(isApplicable(cart)){
            double discount = getDiscount(cart);
            cart.applyDiscount(discount);
        }
        if(next != null) {
            next.applyDiscount(cart);
        } 
    }
    public abstract boolean isApplicable(Cart cart);
    private boolean isCombinable;
    abstract public double getDiscount(Cart cart);
    public abstract String name();
    public Coupon getNext(){
        return next;
    }
    public void setNext (Coupon coupon){
        this.next = coupon;
    }
    public boolean isCombinable(){
        return isCombinable;
    }
    public void setCombinable(boolean isCombinable){
        this.isCombinable = isCombinable;
    }

}
class SeasonalOffer extends Coupon {
    private double percent;
    private String category;
    private DiscountStrategy strat;

    public SeasonalOffer(double pct, String cat) {
        this.percent  = pct;
        this.category = cat;
        this.strat    = DiscountStrategyManager.getInstance()
                            .getStrategy(StrategyType.PERCENT, percent, 0.0);
    }

    @Override
    public boolean isApplicable(Cart cart) {
        for (CartItem item : cart.getItems()) {
            if (item.getProduct().getCategory().equals(category)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public double getDiscount(Cart cart) {
        double subtotal = 0.0;
        for (CartItem item : cart.getItems()) {
            if (item.getProduct().getCategory().equals(category)) {
                subtotal += item.itemTotal();
            }
        }
        return strat.calculate(subtotal);
    }

    @Override
    public String name() {
        return "Seasonal Offer " + (int)percent + "% off " + category;
    }
}

class LoyaltyDiscount extends Coupon {
    private double percent;
    private DiscountStrategy strat;

    public LoyaltyDiscount(double pct) {
        this.percent = pct;
        this.strat   = DiscountStrategyManager.getInstance()
                            .getStrategy(StrategyType.PERCENT, percent, 0.0);
    }

    @Override
    public boolean isApplicable(Cart cart) {
        return cart.isLoyaltyMember();
    }

    @Override
    public double getDiscount(Cart cart) {
        return strat.calculate(cart.getCurrentTotal());
    }

    @Override
    public String name() {
        return "Loyalty Discount " + (int)percent + "% off";
    }
}

class BulkPurchaseDiscount extends Coupon {
    private double threshold;
    private double flatOff;
    private DiscountStrategy strat;

    public BulkPurchaseDiscount(double thr, double off) {
        this.threshold = thr;
        this.flatOff   = off;
        this.strat     = DiscountStrategyManager.getInstance()
                             .getStrategy(StrategyType.FLAT, flatOff, 0.0);
    }

    @Override
    public boolean isApplicable(Cart cart) {
        return cart.getOriginalTotal() >= threshold;
    }

    @Override
    public double getDiscount(Cart cart) {
        return strat.calculate(cart.getCurrentTotal());
    }

    @Override
    public String name() {
        return "Bulk Purchase Rs " + (int)flatOff + " off over " + (int)threshold;
    }
}

class BankingCoupon extends Coupon {
    private String bank;
    private double minSpend;
    private double percent;
    private double offCap;
    private DiscountStrategy strat;

    public BankingCoupon(String b, double ms, double percent, double offCap) {
        this.bank    = b;
        this.minSpend= ms;
        this.percent = percent;
        this.offCap  = offCap;
        this.strat   = DiscountStrategyManager.getInstance()
                            .getStrategy(StrategyType.PERCENT_WITH_CAP, percent, offCap);
    }

    @Override
    public boolean isApplicable(Cart cart) {
        return cart.getPaymentBank().equals(bank)
            && cart.getOriginalTotal() >= minSpend;
    }

    @Override
    public double getDiscount(Cart cart) {
        return strat.calculate(cart.getCurrentTotal());
    }

    @Override
    public String name() {
        return bank + " Bank Rs " + (int)percent + " off upto " + (int)offCap;
    }
}

// ----------------------------
// CouponManager (Singleton)
// ----------------------------
class CouponManager {
    private static CouponManager instance;
    private Coupon head;
    private final Lock lock = new ReentrantLock();

    private CouponManager() {
        this.head = null;
    }

    public static synchronized CouponManager getInstance() {
        if (instance == null) {
            instance = new CouponManager();
        }
        return instance;
    }

    public void registerCoupon(Coupon coupon) {
        lock.lock();
        try {
            if (head == null) {
                head = coupon;
            } else {
                Coupon cur = head;
                while (cur.getNext() != null) {
                    cur = cur.getNext();
                }
                cur.setNext(coupon);
            }
        } finally {
            lock.unlock();
        }
    }

    public List<String> getApplicable(Cart cart) {
        lock.lock();
        try {
            List<String> res = new ArrayList<>();
            Coupon cur = head;
            while (cur != null) {
                if (cur.isApplicable(cart)) {
                    res.add(cur.name());
                }
                cur = cur.getNext();
            }
            return res;
        } finally {
            lock.unlock();
        }
    }

    public double applyAll(Cart cart) {
        lock.lock();
        try {
            if (head != null) {
                head.applyDiscount(cart);
            }
            return cart.getCurrentTotal();
        } finally {
            lock.unlock();
        }
    }
}
public class DiscountCouponSystemDesign {
     public static void main(String[] args) {
        CouponManager mgr = CouponManager.getInstance();
        mgr.registerCoupon(new SeasonalOffer(10, "Clothing"));
        mgr.registerCoupon(new LoyaltyDiscount(5));
        mgr.registerCoupon(new BulkPurchaseDiscount(1000, 100));
        mgr.registerCoupon(new BankingCoupon("ABC", 2000, 15, 500));

        Product p1 = new Product("Winter Jacket", "Clothing", 1000);
        Product p2 = new Product("Smartphone", "Electronics", 20000);
        Product p3 = new Product("Jeans", "Clothing", 1000);
        Product p4 = new Product("Headphones", "Electronics", 2000);

        Cart cart = new Cart();
        cart.addProduct(p1, 1);
        cart.addProduct(p2, 1);
        cart.addProduct(p3, 2);
        cart.addProduct(p4, 1);
        cart.setLoyaltyMember(true);
        cart.setPaymentBank("ABC");

        System.out.println("Original Cart Total: " + cart.getOriginalTotal() + " Rs");

        List<String> applicable = mgr.getApplicable(cart);
        System.out.println("Applicable Coupons:");
        for (String name : applicable) {
            System.out.println(" - " + name);
        }

        double finalTotal = mgr.applyAll(cart);
        System.out.println("Final Cart Total after discounts: " + finalTotal + " Rs");
    }
}
