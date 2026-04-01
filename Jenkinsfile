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
                        script: 'cppcheck --enable=all --addon=misra --error-exitcode=1 --xml --xml-version=2 Static_Code/Reference_Code/ASW/ 2> cppcheck-report.xml', 
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
            recordIssues(
                enabledForFailure: true, 
                tool: cppCheck(pattern: 'cppcheck-report.xml')
            )
            
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