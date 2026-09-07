package TemplateMethodPattern20;


/**
 * ModelTrainingPipeline
 */
interface ModelTrainingPipeline {
    public void dataIngestion();
    public void dataPreprocessing();
    public void buildNetwork();
    public void trainModel();
    public void testModel();
    public void saveModel();
    // template method ie no matter in any order it inherits the methods the flow of execution is going to be the same 
    default void pipleline(){
        dataIngestion();
        dataPreprocessing();
        buildNetwork();
        trainModel();
        testModel();
        saveModel();
    }
}

class linearRegression implements ModelTrainingPipeline{
    @Override
    public void dataIngestion(){
        System.out.println("ingesting the data in the linear regression model ");
    }
    @Override
    public void dataPreprocessing(){
        System.out.println("processing the data in the liner regression model ");
    }
    @Override
    public void buildNetwork(){
        System.out.println("building the linear regression model`");
    }
    @Override
    public void trainModel(){
        System.out.println("training the linear regression model`");
    }
    @Override
    public void testModel(){
        System.out.println("testing the linear regression model`");
    }
    @Override
    public void saveModel(){
        System.out.println("saving the linear regression model`");
    }
}
class logisticRegression implements ModelTrainingPipeline{
    @Override
    public void dataIngestion(){
        System.out.println("ingesting the data in the logistic regression model ");
    }
    @Override
    public void dataPreprocessing(){
        System.out.println("processing the data in the logistic regression model ");
    }
    @Override
    public void buildNetwork(){
        System.out.println("building the logistic regression model`");
    }
    @Override
    public void trainModel(){
        System.out.println("training the logistic regression model`");
    }
    @Override
    public void testModel(){
        System.out.println("testing the logistic regression model`");
    }
    @Override
    public void saveModel(){
        System.out.println("saving the logistic regression model`");
    }
}

public class TemplateMethodPattern {
    public static void main(String[] args) {
        ModelTrainingPipeline linear = new linearRegression();
        ModelTrainingPipeline logistic = new logisticRegression();
        linear.pipleline();
        logistic.pipleline();

    }
}
