package ChainOfResponsibilityDP22;


abstract class MoneyHandler{
    protected MoneyHandler next;
    MoneyHandler(){
        this.next = null;
    }
    public abstract void dispense(int amount);
    public void setNextHandler( MoneyHandler nextHandler){
        this.next = nextHandler;
    }
}

class ThousandHandler extends MoneyHandler{
    private int  numOfNotes;
    ThousandHandler( int numOfNotes){
        this.numOfNotes = numOfNotes;
    }
    @Override
    public void dispense( int amount){
        int notesNeeded= amount/1000;
        if(numOfNotes>=notesNeeded){
            // mtlb araam se deskte hai isko paise 
            numOfNotes= numOfNotes-notesNeeded;
        }
        else{
            // dikkat hojygi sirf numofNotes hi deskte hai isko 
            notesNeeded= numOfNotes;
            numOfNotes =0;
        }
        if(notesNeeded>0)System.out.println("dispensing "+notesNeeded+"thousand notes");
        int pendingAmount= amount - notesNeeded*1000;
        if(pendingAmount>0){
            // then will have tp pass it to the next req handler 
            if(this.next!= null){
                // paass on to the next handler
                next.dispense(pendingAmount);
            }
            else System.out.println("remaining amount cannot be filfilled as there is no next handler");
        }
    }

}
class HundredHandler extends MoneyHandler{
    private int  numOfNotes;
    HundredHandler( int numOfNotes){
        this.numOfNotes = numOfNotes;
    }
    @Override
    public void dispense( int amount){
        int notesNeeded= amount/100;
        if(numOfNotes>=notesNeeded){
            // mtlb araam se deskte hai isko paise 
            numOfNotes= numOfNotes-notesNeeded;
        }
        else{
            // dikkat hojygi sirf numofNotes hi deskte hai isko 
            notesNeeded= numOfNotes;
            numOfNotes =0;
        }
        if(notesNeeded>0)System.out.println("dispensing "+notesNeeded+"hundred notes");
        
        int pendingAmount= amount - notesNeeded*100;
        if(pendingAmount>0){
            // then will have tp pass it to the next req handler 
            if(this.next!= null){
                // paass on to the next handler
                next.dispense(pendingAmount);
            }
            else System.out.println("remaining amount cannot be filfilled as there is no next handler");
        }
    }

}
class FiveHunderedHandler extends MoneyHandler{
    private int  numOfNotes;
    FiveHunderedHandler( int numOfNotes){
        this.numOfNotes = numOfNotes;
    }
    @Override
    public void dispense( int amount){
        int notesNeeded= amount/500;
        if(numOfNotes>=notesNeeded){
            // mtlb araam se deskte hai isko paise 
            numOfNotes= numOfNotes-notesNeeded;
        }
        else{
            // dikkat hojygi sirf numofNotes hi deskte hai isko 
            notesNeeded= numOfNotes;
            numOfNotes =0;
        }
        if(notesNeeded>0)System.out.println("dispensing "+notesNeeded+"five hundred notes");
        int pendingAmount= amount - notesNeeded*500;
        if(pendingAmount>0){
            // then will have tp pass it to the next req handler 
            if(this.next!= null){
                // paass on to the next handler
                next.dispense(pendingAmount);
            }
            else System.out.println("remaining amount cannot be filfilled as there is no next handler");
        }
    }

}
public class CORDP {
    public static void main(String[] args) {
        MoneyHandler thousandHandler = new ThousandHandler(5);
        MoneyHandler fiveHundredHandler = new FiveHunderedHandler(10);
        MoneyHandler hundredHandler = new HundredHandler(20);

        thousandHandler.setNextHandler(fiveHundredHandler);
        fiveHundredHandler.setNextHandler(hundredHandler);

        thousandHandler.dispense(7890);
    }    
}
