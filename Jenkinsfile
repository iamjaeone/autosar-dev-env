pipeline {
    agent any

    stages {
        stage('1. Checkout') {
            steps {
                echo 'Checking out code from GitHub...'
                checkout scm
                
                step([
                    $class: 'GitHubCommitStatusSetter',
                    contextSource: [$class: 'ManuallyEnteredCommitContextSource', context: 'continuous-integration/jenkins/pr-merge'],
                    statusResultSource: [$class: 'ConditionalStatusResultSource', results: [[$class: 'AnyBuildResult', message: 'MISRA Check is running...', state: 'PENDING']]]
                ])
            }
        }

        stage('2. MISRA C Check (Cppcheck)') {
            steps {
                echo 'Starting MISRA C Static Analysis...'
                script {
                    sh 'cppcheck --enable=all --inconclusive --xml Static_Code/Reference_Code/ASW/ 2> cppcheck-result.xml'
                }
            }
        }

        stage('3. Publish Results') {
            steps {
                echo 'Publishing analysis reports...'
                archiveArtifacts artifacts: 'cppcheck-result.xml', allowEmptyArchive: true
            }
        }
    }

    post {
        always {
            echo 'Pipeline finished.'
        }
        success {
            echo 'MISRA Check Passed! Ready to merge.'
            step([
                $class: 'GitHubCommitStatusSetter',
                contextSource: [$class: 'ManuallyEnteredCommitContextSource', context: 'continuous-integration/jenkins/pr-merge'],
                statusResultSource: [$class: 'ConditionalStatusResultSource', results: [[$class: 'AnyBuildResult', message: 'MISRA Check Passed!', state: 'SUCCESS']]]
            ])
        }
        failure {
            echo 'MISRA Check Failed. Please review the report.'
            step([
                $class: 'GitHubCommitStatusSetter',
                contextSource: [$class: 'ManuallyEnteredCommitContextSource', context: 'continuous-integration/jenkins/pr-merge'],
                statusResultSource: [$class: 'ConditionalStatusResultSource', results: [[$class: 'AnyBuildResult', message: 'MISRA Check Failed.', state: 'FAILURE']]]
            ])
        }
    }
}
