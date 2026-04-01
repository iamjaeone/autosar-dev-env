pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('MISRA C Check') {
            steps {
                script {
                    def status = sh(
                        script: 'cppcheck --addon=misra --error-exitcode=1 Static_Code/Reference_Code/ASW/',
                        returnStatus: true
                    )
                    
                    if (status != 0) {
                        error "MISRA C compliance check failed!"
                    }
                }
            }
        }
    }
    
    post {
        always {
            echo "Pipeline finished."
        }
        success {
            echo "MISRA C Passed. PR is ready to merge!"
        }
        failure {
            echo "MISRA C Failed. Fix the violations."
        }
    }
}
